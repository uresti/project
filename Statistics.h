#include "Statistics.h"

class Bank
{
public:
    int vplace; //Vector placement
    int a_num; //Account number ~Has been removed.
    int low; //~Has been removed.

    Customer* all;
    
    Bank()
    : all(new Customer[100]),vplace(0),a_num(600001),low(100){}
    
    void fill();
    void create(Statistics& Info);
    void close(Statistics& Info);
    void withdraw(int a_number,Statistics& Info);
    void deposit(int a_number,Statistics& Info);
    void account_balance(int a_number);
    void transactions(int a_number);
};
