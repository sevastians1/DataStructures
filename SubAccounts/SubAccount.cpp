#include "SubAccount.h"
void SubAccount::deposit(unsigned int amount) {
        if(amount < 0) {
            cout<<endl<<"Cannot deposit negative amount"<<endl; 
            return;}
        balance += amount;
        cout<<endl<<"Successfully deposited balance: "<<balance<<endl; 
        return;}

    //withdraw cannot make balance negative, also virtual 
void SubAccount::withdraw(unsigned int amount) { 
        if (amount > balance) {
            cout<<endl<<"Cannot withdraw money that is not there"<<endl; 
            return;}
        balance -= amount;
        cout<<endl<<"Successfully withdrew, balance is now: "<<balance<<endl; 
        return;}

    //defining a default menu option, will call menu contents to print out the menu and intiate the loop
    void SubAccount::menu(){
        char userChoice='0';
        while(userChoice!='X'){
        cout<<"Eligiable services for Sub-Account:"<<accountNumber<<endl;
        cout<<getMenuContents()<<endl;
        cin>>userChoice;
        userChoice=toupper(userChoice);
        userChoiceReaction(userChoice);
        // //was having issues with cin taking different input types, clearing here helped resolve error
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    //function will take input generated by the menu option and call methods based on that
    //it is virtual because it will be redefined in the checking account
    //all user input is dealt with inside the case, so that the functions remain pure
void SubAccount::userChoiceReaction(char choice){
        switch(choice){
            case 'D':{
                unsigned int amountToDeposit;
                cout<<"Please enter the amount to deposit"<<endl;
                cin>>amountToDeposit;
                deposit(amountToDeposit);
                break;
            }
            case 'W':{
                unsigned int amountToWithdraw;
                cout<<"Please enter the amount to withdraw"<<endl;
                cin>>amountToWithdraw;
                withdraw(amountToWithdraw);
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
        //in order to change menu's, this function must be in checking, so this is virtual
string SubAccount::getMenuContents() const {
        return " D -- Deposit \n W -- Withdraw \n X -- Exit \n Please enter your selection: \n";
    }