#include "Statistics.h"


void create()
{

    Bank All;
	
    string fname;
    string lname;
    
    int pin=0;
    int a_num=600001;

    cout << "Enter your first and last name:\n";
    cin >> fname >> lname;
	
    pin=rand() % 9000 + 1000;
    
    Account* A= new Account(fname,lname,a_num,pin,1000);
    
    cout << "Your account number is " << a_num << " and your pin number is " << pin << ".\n";
    cout << "Your beginning balance is $1000.\n";
    
    All->all[All->a_numm]=*A;
    ++All->a_numm;
}

int main()
{
    cout << "This is your Piggy Bank. Welcome valued customer.\n";
    int operation=0;
    cout    << "Please select one of these operations (enter a number): \n"
            << "1. Open a new account.\n"
            << "2. Close the existing account.\n"
            << "3. Withdraw money (up to $500).\n"
            << "4. Deposit money.\n"
            << "5. Account balance.\n"
            << "6. List the last 10 transactions.\n"
            << "7. Statistical information.\n\n";
    cin     >> operation;
    if(operation==1) create();
}
