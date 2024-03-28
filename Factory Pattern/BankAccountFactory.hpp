#ifndef BANKACCOUNTFACTORY_HPP
#define BANKACCOUNTFACTORY_HPP

#include <iostream>
#include "BankAccount.hpp"
#include "PersonalAccount.hpp"
#include "CheckingsAccount.hpp"
using namespace std;

class BankAccountFactory {
    private:
    BankAccount * bankaccount;
    public:
    BankAccount* createAccount(string type) {
        if(type == "P") {
            bankaccount = new PersonalAccount();
        }
        else if(type == "C") {
            bankaccount = new CheckingsAccount();
        }

        return bankaccount;
    }
};

#endif