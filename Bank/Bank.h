#include "BankAccount.h"

class Bank{
    private:
        string name;
        string address;
        string workingHours;
        static string const menuContents;
        map<string, BankAccount*> accountsContainer;
    public:
        //constructors
        Bank() : name(""), address(""), workingHours(""){};
        Bank(string name, string address, string workingHours){
            this->name = name;
            this->address = address;
            this->workingHours = workingHours;
        }
        //deconstructor
        ~Bank(){
            for(auto& pointer: accountsContainer){
                delete pointer.second;
            }
            accountsContainer.clear();
        }
        //basic functionality
        //return a vector of the container
        vector <BankAccount*> accountVector(){
            vector <BankAccount*> accountsVector;
             for(auto& bankAccount: accountsContainer){
                accountsVector.push_back(bankAccount.second);
            }
            return accountsVector;
        }
        //return the aggregated bank balance of all acounts
        unsigned int bankAggregatedBalance(){
            unsigned int aggregatedBalance=0;
            for(auto& bankAccount: accountsContainer){
                aggregatedBalance+=bankAccount.second->getBalance();
            }
            return aggregatedBalance;  
        }
        //return basic bank info used later
        void printBankInfo(){
            cout<<"Bank Name: "<<name<<endl;
            cout<<"Bank Address" <<address<<endl;
            cout<<"Bank Working Hours: "<<workingHours<<endl;
            cout<<"Aggregated Bank Balance: "<<bankAggregatedBalance()<<endl;
            cout<<"Consists of "<<accountsContainer.size()<<" Bank Accounts"<<endl<<endl;
        }        
        //menu functions
        void menu(){
                char userChoice='0';
                while(userChoice!='X'){
                    cout<<"Welcome to: "<<name<<". What would you like to do?"<<endl;
                    cout<<menuContents<<endl;
                    cin>>userChoice;
                    userChoice=toupper(userChoice);
                    userReactionChoice(userChoice);
                    //was having issues with cin taking different input types, clearing here helped resolve error
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

        void userReactionChoice(char userChoice){
                switch(userChoice){
                    case 'A':{
                        //number of bank accounts
                        numberOfBankAccounts();
                        break;
                    }
                    case 'S':{
                         //number of savings accounts
                        numberOfSavingAccounts();
                        break;
                    }
                    case 'H':{
                         //number of checkings accounts
                        numberOfCheckingAccounts();
                        break; 
                    }
                    case 'O':{
                        //open bank account
                        string fname;
                        string lname;
                        int ssn;
                        cout<<"Please enter first name"<<endl;
                        cin>>fname;
                        cout<<"Please enter last name"<<endl;
                        cin>>lname;
                        cout<<"Please enter Social Security Number"<<endl;
                        cin>>ssn;
                        openBankAccount(fname, lname, ssn);
                        break;
                    }
                    case 'C':{
                        //close bank account
                        string bankAccountNumber;
                        cout<<"Please enter a bank account to delete"<<endl;
                        cin>>bankAccountNumber;
                        closeBankAccount(bankAccountNumber);
                        break;
                    }
                    case 'M':{
                        //modify bank account(calls the menu of bank account)
                        string bankAccountNumber;
                        cout<<"Please enter a bank account to modify"<<endl;
                        cin>>bankAccountNumber;
                        modifyBankAccount(bankAccountNumber);
                        break;
                    }  
                    case 'D':{
                        //detailed bank accounts
                        seeAllAccounts();
                        break; 
                    } 
                    case 'B':{
                        //Brief bank-accounts sorted by aggregated balance
                        briefBankInfo();
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

        void numberOfBankAccounts() {
            if(accountsContainer.size()){
                cout<<"Number of Bank-Accounts: "<<accountsContainer.size()<<endl;
            }
            else{
                cout<<"There are no accounts in this bank"<<endl;
            }
        }
        void numberOfSavingAccounts(){
            int totalSavings=0;
            //we search each bank account
            for(auto& BankAccount:accountsContainer){
                //in each bank account we search every sub account
                for(auto& SubAccount:BankAccount.second->getAccountContainer()){
                    //we check if current account is a savings or a checkings through dynamic cast
                    SavingAccount* savingPtr = dynamic_cast<SavingAccount*>(SubAccount.second);
                    if (savingPtr != nullptr){
                        totalSavings++;
                    }
                }
            }
            cout<<"There are a total of: "<<totalSavings<<" Savings accounts active"<<endl;
        }
        void numberOfCheckingAccounts(){
            int totalCheckings=0;
            //we search each bank account
            for(auto& BankAccount:accountsContainer){
                //in each bank account we search every sub account
                for(auto& SubAccount:BankAccount.second->getAccountContainer()){
                    //we check if current account is a savings or a checkings through dynamic cast
                    CheckingAccount* checkingPointer = dynamic_cast<CheckingAccount*>(SubAccount.second);
                    if (checkingPointer != nullptr){
                        totalCheckings++;
                    }
                }
            }
            cout<<"There are a total of: "<<totalCheckings<<" checking accounts active"<<endl;
        }

        void openBankAccount(string fname, string lname,  int ssn){
            BankAccount* newAccount=new BankAccount(Owner(fname, lname, ssn));
            accountsContainer.emplace(newAccount->getAccountNumber(), newAccount);
            cout<<"Your new account number is: "<<newAccount->getAccountNumber()<<endl;

        }

        void closeBankAccount(string bankAccountNumber){
            //creating the iterator that is used to find the account
            map<string, BankAccount*>::iterator foundAccount=accountsContainer.find(bankAccountNumber);
            if(foundAccount!=accountsContainer.end()){ //if it exists in this container
                delete foundAccount->second; //deleting the contents at the pointer to prevent memory leak
                accountsContainer.erase(bankAccountNumber);
            }
            //was having issues with cin taking different input types, clearing here helped resolve error
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<bankAccountNumber<<" has been deleted"<<endl;
        }

        void modifyBankAccount(string bankAccountNumber){
            if(accountsContainer.find(bankAccountNumber)!=accountsContainer.end()){ //if it exists in this container
            //bank account deals with it's own services with encapsulation
                accountsContainer.find(bankAccountNumber)->second->menu();
            }
            else{cout<<endl<<"Please enter a valid account number"<<endl;}
        }
        //detailed bank accounts
        void seeAllAccounts(){
            printBankInfo();
            for(auto& bankAccount: accountsContainer){
                bankAccount.second->briefAccountInfo();
                bankAccount.second->getBalance();
            }
        }

        void briefBankInfo(){
            printBankInfo();
            if(accountsContainer.size()==0){return;}
            vector <BankAccount*> accountsVector=accountVector();
            RadixSort(accountsVector);
             for(auto& bankAccount: accountsVector){
                cout<<"Aggregated Balance of the bank account : "<<bankAccount->getAccountNumber()<<endl;
                cout<<" with "<<bankAccount->amountOfSubAccounts()<< " sub-accounts is "<<bankAccount->getBalance()<<endl;
             }
        
        
        }
            















};
//same with previous class, menu contents unchanging in a single memory location
string const Bank::menuContents=" A -- Number of Bank-Accounts \n S -- Number of Saving-Accounts \n H -- Number of Checking-Accounts"
        "\n O -- Open a Bank-Account \n C -- Close a Bank Account \n M -- Modify Bank Account \n"
        " D -- Detailed Account Info \n B -- Brief Bank-Accounts Sorted based on Aggregated Balances \n X -- Exit \n Please enter your selection: \n";