#include "Customer.h"

class Bank
{
    int anum;
    int a_num;
public:
    Account* all;
    
    int callanum()  {return anum;};
    int calla_num() {return a_num;};
    
    int addanum()   {return ++anum;};
    int add_anum()  {return ++a_num;};
    
    Bank()
    : all(new Account[100]),anum(1),a_num(600001){}
};
