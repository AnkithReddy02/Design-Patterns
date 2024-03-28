#ifndef PERSONALACCOUNT_HPP
#define PERSONALACCOUNT_HPP

#include "BankAccount.hpp"
#include <iostream>
using namespace std;

class PersonalAccount: public BankAccount {
public:
    PersonalAccount() {
        cout << "Personal Account Created!" << endl;
    }
    bool verifyUserIdentity() {
        return false;
    } 
};

#endif