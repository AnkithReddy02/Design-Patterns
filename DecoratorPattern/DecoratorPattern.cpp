/*
This pattern is required to avoid **Class Explosion** --> Happens when you create combination of *toppings*
as classes!

Use cases:
1. Pizza Shop
2. Car Shop
3. Coffee Shop
*/

#include<bits/stdc++.h>
using namespace std;

class ICoffee {
public:
    virtual ~ICoffee() {}
    virtual int cost() = 0;
};

class Expresso : public ICoffee {
public:
    int cost() override {
        return 10;
    }
};

class Mocha : public ICoffee {
public:
    int cost() override {
        return 7;
    }
};

// --------------------------

class IDecorator: public ICoffee {
public:
    virtual ~IDecorator() {}
    
};

class ExtraMilk: public IDecorator {
public:
    ICoffee *coffee;
    ExtraMilk(ICoffee* coffee) : coffee(coffee) {

    }

    int cost() override {
        return coffee->cost() + 1;
    }
};


class ExtraCream: public IDecorator {
public:
    ICoffee *coffee;
    ExtraCream(ICoffee* coffee) : coffee(coffee) {

    }

    int cost() override {
        return coffee->cost() + 3;
    }
};

int main() {
    ICoffee* coffee = new ExtraMilk(new ExtraCream(new ExtraMilk(new Mocha())));
    cout << "Total Cost: " << coffee->cost() << endl;
}