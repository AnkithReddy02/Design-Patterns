#include<iostream>
#include "FlyWithWings.hpp"
#include "FlyWithLegs.hpp"
using namespace std;

class Duck {
    private:
    FlyInterface* fi;
    public:
    Duck(FlyInterface * fi) : fi(fi) {}
    void performFly() {
        fi->fly();
    }
};

class MallardDuck : public Duck {
    public:
    MallardDuck() : Duck(new FlyWithLegs()) {}
};

int main() {
    MallardDuck* md = new MallardDuck();

    md->performFly();
}