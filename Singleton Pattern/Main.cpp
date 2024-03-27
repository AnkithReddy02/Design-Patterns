#include<iostream>
#include "Singleton.hpp"
using namespace std;

int main() {
    Singleton * singleton_1 = Singleton::getInstance();

    singleton_1->setVal(20);

    cout << "singleton_1 val --> " << singleton_1->getVal() << endl;

    Singleton * singleton_2 = Singleton::getInstance();

    cout << "singleton_2 val --> " << singleton_2->getVal() << endl;
}