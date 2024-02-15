#ifndef RADIX_H
#define RADIX_H

#include "BankAccount.h"
//all radix functionality has template so Bank can pull it too
    template <typename T>
    unsigned int radixGetMax(vector<T*>& accounts){
        unsigned int max=accounts[0]->getBalance();
        for(const auto& subAccount: accounts){
            if(subAccount->getBalance()>max){
                max=subAccount->getBalance();
            }
        }
            //returns the largest balance number
            return max;
    }
    template <typename T>
    void countingSort(vector<T*>& accounts, unsigned int exp){
        const int BASE=10;
        //define 2 bins for radix sort
        vector<T*> output(accounts.size(), 0);
        vector<int> count(BASE, 0);
        //count the occurences at each digit place
        for (unsigned int i = 0; i < accounts.size(); i++) {
            count[(accounts[i]->getBalance() / exp) % BASE]++;
        }
        //gets the cumulative count
        for (int i = 1; i < BASE; i++) {
            count[i] += count[i - 1];
        } 
            //builds the output vector
            //int is long type here because unsigned causes issues
        for(long int i=accounts.size()-1; i>=0; i--){
            output[count[(accounts[i]->getBalance() / exp) % BASE] - 1] = accounts[i];
            count[(accounts[i]->getBalance() / exp) % BASE]--;  
        }
        //copies the output vector so that it contained the sorted numbers
        for (unsigned int i = 0; i < accounts.size(); i++) {
            accounts[i] = output[i];
        }
    }
        //completed sort that will call each previous function to fully sort 
    template <typename T>
    void RadixSort(vector <T*>& accounts){
        unsigned int max=radixGetMax(accounts);
        for(unsigned int exp=1; max/exp>0; exp*=10){
            countingSort(accounts, exp);
        }
        }

#endif
