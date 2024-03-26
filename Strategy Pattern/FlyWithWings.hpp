#ifndef FLYWITHWINGS_HPP
#define FLYWITHWINGS_HPP


#include "FlyInterface.hpp"
#include <iostream>
using namespace std;

class FlyWithWings : public FlyInterface {
    public:
        void fly() {
            cout << "Fly With Wings ;)" << endl;
        }
};

#endif