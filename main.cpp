#include "Bank/Bank.h"

void interface(){
    string name;
    string address;
    string workingHours;
    cout<<"Enter the name of your bank: "<<endl;
    getline(cin, name);
    cout<<"Enter the address of your bank: "<<endl;
    getline(cin, address);
    cout<<"Enter the working hours of your bank: "<<endl;
    getline(cin, workingHours);
    Bank bank=Bank(name, address, workingHours);
    bank.menu();
}


int main(){
    interface();



 return 0;   
}