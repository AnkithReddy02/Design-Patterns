#include <iostream>
using namespace std;

#include "Branch.hpp"
#include "BankAccountFactory.hpp"

int main() {
    Branch * branch = new Branch(new BankAccountFactory());
    branch->openAccount("C");

}