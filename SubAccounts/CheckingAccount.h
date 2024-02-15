#include "SubAccount.h"
//inheritted from SubAccount
class CheckingAccount: public SubAccount{
    private:
        static int accountID;
        unsigned int maximumCapacity=0;
        bool locked;

    public:
        //constructors
        void constructorCommonality(){
            accountNumber="CHK"+to_string(accountID);
            accountID++;
        }
        //adds the account number to the constructor
        //constructor, initialized the balance and maxCapacity to 0, and locked, unless given otherwise
        CheckingAccount(){
            constructorCommonality();
            this->balance = 0;
            this->maximumCapacity=0;
            this->locked=true;
        }
        CheckingAccount(unsigned int balance, unsigned int maximumCapacity, bool locked){
            constructorCommonality();
            this->balance=balance;
            this->maximumCapacity=maximumCapacity;
            this->locked=locked;
        }

        //getters and setters
        void getMaximumCapacity(){
            cout<<"Your Maximum Capacity is: "<<maximumCapacity<<endl;
        }
        void getLockedStatus(){
            cout<<"Your Account is "<<(locked? "locked" : "unlocked")<<endl;
        }        
        void setMaxCapacity(unsigned int amount) {
            maximumCapacity = amount;
            cout<<endl<<"Your new maximum capacity is "<<maximumCapacity<<endl;}
            
        void setLocked() {
            this->locked=!locked;
            cout<<endl<<"Your account is now "<<(locked? "locked" : "unlocked")<<endl;}

        //override deposit and withdraw with appropriate functionality
        void deposit(unsigned int amount) override{
            if(locked){
                isLockedText();
                return;
            }
            if (balance+amount > maximumCapacity){
                cout<<endl<<"You cannot deposit more than the maximum capacity"<<endl;
                return;
            }
            SubAccount::deposit(amount);
            return;
        }

        void withdraw(unsigned int amount) override{
            if(locked){
                 isLockedText();
                 return;
            }
            SubAccount::withdraw(amount);
            return;           

        }
        //a simple implementation to call a function when account is locked
        void isLockedText(){
            cout<<endl<<"Account is locked, please unlock to use transaction"<<endl;
        }

        //redefined user choice that will load more functionality upon entering the menu
        //brackets are included in each switch, to deal with control/scope issues
        void userChoiceReaction(char choice) override{
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
                    //exiting is handled by the parent function
                case 'C':{
                    unsigned int maxCapacity;
                    cout<<"Please enter the maximum capacity"<<endl;
                    cin>>maxCapacity;
                    setMaxCapacity(maxCapacity);
                    break;
                }
                case 'L':{
                    setLocked();
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
        //menu contents overridden as well so parent's menu function has the appropriate text
        string getMenuContents() const override {
            return " D -- Deposit \n W -- Withdraw \n C -- Max Capacity \n L -- Lock or Unlock Account\n"
            " X -- Exit \n Please enter your selection: \n";
        }




};
//static variable we will use to give unique account ID to 
int CheckingAccount::accountID = 6000;