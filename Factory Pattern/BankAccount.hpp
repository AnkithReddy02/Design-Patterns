#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP

class BankAccount {
public:
    virtual bool verifyUserIdentity() = 0;
};

#endif