#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
//had to define this ifndef because my radix sort is in a seperate file to increase readablity and
//allow upper level file to use the same code, but Radix requires most functionality in this file
#include "../SubAccounts/SavingAccount.h"
#include "../SubAccounts/CheckingAccount.h"
#include "Owner.h"
#include "Radix.h"
class BankAccount{
    private:
        static int accountID;
        string accountNumber;
        Owner owner;
        //storing accounts as map for O(logn) access and will construct a vector for sorting requests
        //storing as the parent account pointer allows for both children to be stored in the same container
        //stored on account number, and pointer
        map<string, SubAccount*>  accountContainer;
        bool firstSavings=true;
        //defining this string as const and static to save memory for something that will remain the same across classes
        static string const menuContents;

    public: 
        //constructor and deconstructor
        BankAccount(Owner owner){
            this->owner = owner;
            accountNumber="BNK"+to_string(accountID);
            accountID++;
        }
        //deconstructor deallocates the memory in the account container pointer, then clears the map to prevent memory leak
        ~BankAccount(){
            for(auto& pointer: accountContainer){
                delete pointer.second;
            }
            accountContainer.clear();
        }
        //getters and setters, they are defined as needed, but there are not many needed in general
        map<string, SubAccount*> getAccountContainer() { return accountContainer; }

        string getAccountNumber() { return accountNumber; }
        //basic functionality getters
        unsigned int amountOfSubAccounts(){
            return accountContainer.size();
        }
        //get balance is named this name so radix sort can be used without defining another radix function
        unsigned int getBalance(){
            unsigned int aggragatedBalance=0;
            //loops through all sub-accounts in container and returns total balance
            for(auto& subAccount: accountContainer){
                aggragatedBalance+=(subAccount.second->getBalance());
            }
            return aggragatedBalance;
        }
        //menu functions
        void menu(){
            char userChoice='0';
            while(userChoice!='X'){
                //was having issues with cin taking different input types, clearing here helped resolve error
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<endl<<"Welcome "<<owner.getFirstName()<<" "<<owner.getLastName()<<endl;
                cout<<"Eligible services for Bank-Account:"<<accountNumber<<endl;
                //menu contents is a private data member here
                cout<<menuContents<<endl;
                cin>>userChoice;
                userChoice=toupper(userChoice);
                userReactionChoice(userChoice);
            }
        }
        //similar to previous, user reaction choice is defined here
        //most cin is going in the switch statements so functions can remain pure and polymorphic/able to be used elsewhere
        void userReactionChoice(char userChoice){
            switch(userChoice){
                case 'S':{
                    //open savings
                    unsigned int amountToDeposit;
                    cout<<"Please enter the initial savings amount"<<endl;
                    cin>>amountToDeposit;
                    openSaving(amountToDeposit);
                    break;
                }
                case 'C':{
                    //open checkings
                    unsigned int amountToDeposit;
                    cout<<"Please enter the initial checking amount"<<endl;
                    cin>>amountToDeposit;
                    unsigned int maximumCapacity;
                    cout<<"Please enter the maximum capacity"<<endl;
                    cin>>maximumCapacity;
                    char isLockedString;
                    cout<<"If you would like to initally lock your account enter T, otherwise enter F"<<endl;
                    cin>>isLockedString; 
                    bool isLocked=(toupper(isLockedString)=='T');
                    openChecking(amountToDeposit, maximumCapacity, isLocked);
                    break;
                }
                case 'M':{
                    //modify account
                    string accountToModify="";
                    cout<<"Please enter the account number to modify"<<endl;
                    cin>>accountToModify;
                    modifySubAccount(accountToModify);
                    break; 
                }
                case 'G':{
                    string accountToDelete="";
                    //delete account
                    cout<<"Please enter the account number to delete"<<endl;
                    cin>>accountToDelete;
                    deleteAccount(accountToDelete);
                    break;
                }
                case 'D':{
                    //detailed bank account info sorted based on balances of sub-accounts
                    cout<<"All bank accounts based on balance"<<endl;
                    accountsByBalance();
                    break;
                }
                case 'B':{
                    //brief bank account info
                    briefAccountInfo();
                    break;
                }
                case 'X':{
                    cout<<"Goodbye"<<endl;
                    break;
                }
                default:{
                    cout<<endl<<"Please enter a valid choice"<<endl;
                    break;
                }
            }
        }        
        //functionality as defined in menu
        void openSaving(unsigned int initialAmount){
            //first account gets 100;
            if(firstSavings){ 
                initialAmount +=100;
                firstSavings=false;
            }
            //creating new account and saving in map with the pointer
            SavingAccount* newSavingPointer=new SavingAccount(initialAmount);
            accountContainer.emplace(newSavingPointer->getAccountNumber(), newSavingPointer);
            cout<<endl<<"Your savings account was successfully created. \n Your new account number is : "
            <<newSavingPointer->getAccountNumber()<<endl;
        }

        void openChecking(unsigned int initialAmount, unsigned int maximumAmount, bool isLocked){
            //creating new account and saving in map with the pointer
            CheckingAccount* newCheckingPointer=new CheckingAccount(initialAmount, maximumAmount, isLocked);
            accountContainer.emplace(newCheckingPointer->getAccountNumber(), newCheckingPointer);
            cout<<endl<<"Your savings account was successfully created. \n Your new account number is : "
            <<newCheckingPointer->getAccountNumber()<<endl;
        }
        
        void modifySubAccount(string subAccountNumber){
            if(accountContainer.find(subAccountNumber)!=accountContainer.end()){ //if it exists in this container
                accountContainer.find(subAccountNumber)->second->menu();//call menu which you can use to modify 
            }
            else{//it doesn't exist at this bank account
                cout<<endl<<"Please enter a valid account number"<<endl;
            }
        }

        void deleteAccount(string subAccountNumber){
            //creating the iterator that is used to find the account
             map<string, SubAccount*>::iterator foundContainer=accountContainer.find(subAccountNumber);
            if(foundContainer!=accountContainer.end()){ //if it exists in this container
                delete foundContainer->second; //deleting the contents at the pounsigned inter to prevent memory leak
                accountContainer.erase(subAccountNumber);
                cout<<subAccountNumber<<" has been deleted"<<endl;
            }
            else{//if you can't find the account
                cout<<"Enter a valid account number"<<endl;
            }
        }
        //converts our map container to vector
        vector <SubAccount*> getVectorAccounts(){
            vector <SubAccount*> accounts;
            for (auto& accountMap : accountContainer){
                accounts.push_back(accountMap.second);
            };
            return accounts;
        }

         //detailed bank account info sorted based on balances of sub-accounts
        void accountsByBalance(){
            vector <SubAccount*> accounts=getVectorAccounts();
            if(accounts.size()==0){ //if there are no accounts, return
            cout<<"No accounts"<<endl;
            return;
            }
            //basically sorting our vector using radix functionality from seperate file
            RadixSort(accounts);
            //loop through vector and print based on sorted vector
            for(unsigned int i=0; i<accounts.size(); i++){
                cout<<"\nAccount number: "<<accounts.at(i)->getAccountNumber()<<endl;
                cout<<"Balance: "<<accounts.at(i)->getBalance()<<endl;
                //if block so we can access the further fuctionality in checkings, but ONLY if 
                //the current account is a checking account, based on attempting to caste the account as checking account
                CheckingAccount* checkingPtr = dynamic_cast<CheckingAccount*>(accounts.at(i));
                if (checkingPtr != nullptr){
                    checkingPtr->getMaximumCapacity();
                    checkingPtr->getLockedStatus();
                }

            }
        }
        void briefAccountInfo(){
            cout<<"Bank Account Number: "<<accountNumber<<endl;
            cout<<"Name: "<<owner.getFirstName()<<" "<<owner.getLastName()<<endl;
            cout<<"Social Secuity Number: "<<owner.getSSN()<<endl;
            cout<<"\nBank account "<<accountNumber<<" has "<<amountOfSubAccounts();
            cout<<" sub-accounts and an aggregated balance of " <<getBalance()<<endl;
        }









};
int BankAccount::accountID = 10000;
//static info that is the same for every class
string const BankAccount::menuContents=" S -- Open Savings Sub-Account \n C -- Open Checkings Sub-Account \n M -- Modify a Sub Account"
        "\n G -- Close a Sub-Account \n D -- Detailed Bank Account Info Based on Balances \n"
        " B -- Brief Bank Account Info \n X -- Exit \n Please enter your selection: \n";
#endif