#include "Statistics.h"

Account* called = new Account("Default","Default",0,1,0);

void fill(Bank& All) //Fill the bank with default accounts
{
    for(int i=0;i<100;++i)
    {
        All.all[i]=*called;
    }
}

void out(Bank& All) //Write out what is stored in Bank
{
    ofstream ofs1("Bank.txt", ofstream::out); 
    
    for(int i=1;i<All.callvplace();++i)
    {
        *called=All.all[i];
        if(called->balance!=0)
        {
            ofs1 << "[ customer " << called->first_name << ' ' << called->last_name << endl;
            ofs1 << "  account " << called->account_number << endl;
            ofs1 << "  PIN " << called->pin_number << endl;
            ofs1 << "  balance " << called->balance << endl;
            ofs1 << "  transcations { ";
            for(int j=1;j<11;++j)
            {
                ofs1 << '(' << called->transactions[j] << ") ";
            }
            ofs1 << "}" << endl;
            ofs1 << ']' << endl;
        }
    }
}

void create(Bank& All)
{
    string fname;
    string lname;
    
    int pin=0;
    
    cout << "Enter your first and last name:\n";
    cin >> fname >> lname;
    
    pin=rand() % 9000 + 1000;
    
    Account* A= new Account(fname,lname,All.calla_num(),pin,1000);
    
    cout << "Your account number is " << All.calla_num() << " and your pin number is " << pin << ".\n";
    cout << "Your beginning balance is $1000.\n";
    
    All.all[All.callvplace()]=*A;
    All.addvplace() && All.add_anum();
}


int main()
{
    Bank All;
    fill(All); 
    
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
    
    if(operation==1) create(All);
    out(All);
}
