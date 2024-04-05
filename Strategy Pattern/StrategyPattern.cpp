#include<iostream>
#include "FlyWithWings.hpp"
#include "FlyWithLegs.hpp"
using namespace std;


/*

    Follows SOLID Principles"

    1. Single Responsibility Principle:
        A class should have one, and only one reason to change.
        Example: 
            Fly Interface - Has only one responsibility that is Fly.

    2. Open Closed Principle:
        Example: 
            Open for Extension: You can add more Fly Behaviors
            Closed for Modification: There is no requirement of modifying Duck Class.

    3. Liskov Substitution Principle:
        Objects of superclass should be able to replace with subclass.
        Example: 
            Like, Duck * duck = new MallardDuck();

    4. Interface Segregation Principle:
        No client should be forced to implement methods/behaviors that are not required
        Example:
            ----

    5. Dependency Inversion Principle:
        A class shouldn't depend on concrete entities rather it should depend on **abstract** entities.
        Example:
            FlyInterface * fi in Duck



*/

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

class RubberDuck : public Duck {
    public:
    RubberDuck() : Duck(new FlyWithWings()) {}
};

class RandomDuck : public Duck {
    public:
    RandomDuck() : Duck(new FlyWithLegs()) {}
};



int main() {
    Duck* md = new MallardDuck();

    md->performFly();
}