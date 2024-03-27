#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include<iostream>

class Singleton {

    private:
    static Singleton * singleton;
    int val;
    Singleton() {
        
    }
    public:
    static Singleton* getInstance() {
        if(singleton == NULL) {
            singleton = new Singleton();
        }

        return singleton;
    }
    void setVal(int x) {
        this->val = x;
    }
    int getVal() {
        return val;
    }
};

// ** NOT CLEAR **
// Why Data Type should be mentioned again?
Singleton* Singleton::singleton = nullptr;

#endif