#ifndef FLYWITHLEGS_HPP
#define FLYWITHLEGS_HPP

#include "FlyInterface.hpp"
#include <iostream>
using namespace std;

class FlyWithLegs : public FlyInterface {
    public:
        void fly() {
            cout << "Fly With Legs ||" << endl;
        }
};

#endif