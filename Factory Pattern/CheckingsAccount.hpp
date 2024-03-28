#ifndef CHECKINGSACCOUNT_HPP
#define CHECKINGSACCOUNT_HPP

#include "BankAccount.hpp"
#include <iostream>
using namespace std;

class CheckingsAccount: public BankAccount {
public:
    CheckingsAccount() {
        cout << "Checkings Account Created!" << endl;
    }
    bool verifyUserIdentity() {
        return false;
    } 
};

#endif