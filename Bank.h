#include "Customer.h"

class Bank
{
public:
    Account* all;
    Account* Accounts= new Account[100];
    
    Bank()
    : all(Accounts) {}
};
