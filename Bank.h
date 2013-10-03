#include "Customer.h"

class Bank
{
public:
    int vplace; //Vector placement
    int a_num; //Account number
    int low;

    Account* all;
    
    /*int callvplace()  {return vplace;};
    int calla_num() {return a_num;};
    int calllow() {return low;};
    
    int addvplace()   {return ++vplace;};
    int add_anum()  {return ++a_num;};*/
    
    
    Bank()
    : all(new Account[100]),anum(1),a_num(600001){}
};
