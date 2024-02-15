#include "SubAccount.h"
//inheritted from SubAccount
class SavingAccount: public SubAccount {
    private:
        static int accountID;
    public:
        //adds the account number to the constructor
        //constructor, initialized the balance to 0, unless balance is included in the parameter
        SavingAccount(){
            this->balance = 0;
            accountNumber="SAV"+to_string(accountID);
            accountID++;
        }
        SavingAccount(unsigned int balance){
            this->balance=balance;
            accountNumber="SAV"+to_string(accountID);
            accountID++;
        }
        
        //


        
    



};
//static variable we will use to give unique account ID to 
int SavingAccount::accountID = 1000;