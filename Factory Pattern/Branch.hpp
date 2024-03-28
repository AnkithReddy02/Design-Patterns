#ifndef BRANCH_HPP
#define BRANCH_HPP

#include "BankAccountFactory.hpp"
#include "BankAccount.hpp"

class Branch {
    private:
    BankAccountFactory* factory;
    public:
    Branch(BankAccountFactory * factory) : factory(factory) {}

    BankAccount* openAccount(string type) {
        return factory->createAccount(type);
    }
};

#endif