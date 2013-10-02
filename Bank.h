#include "Customer.h"

class Bank
{
public:
    Account* all=new Account[100];
    Account* Accounts= new Account[100];
    
    Bank()
    : all(Accounts) {}
};
