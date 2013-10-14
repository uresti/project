#include "Bank.h"

istream& operator>>(istream& is, Bank& All) //Cin bank.
{
    Customer* called = new Customer("Default","Default",0,1,0);
    
    ifstream f_in("Bank.txt",ios::in);
    
    string next;
    string first;
    string last;
    string transaction;
    string T;
    int account;
    int pin;
    double balance;
    
    while(!f_in.eof())
    {
        f_in >> next;
        
        if(next=="customer") //Get first and last name.
        {
            f_in >> first;
            f_in >> last;
        }
        if(next=="account") //Get the account number.
        {
            f_in >> account;
        }
        if(next=="PIN") //Get pin.
        {
            f_in >> pin;
        }
        if(next=="balance") //Get balance.
        {
            f_in >> balance;
            Customer A(first,last,account,pin,balance);
            All.all[All.vplace]=A;
        }
        if(next=="{") //Get transactions.
        {
            for(int i=1;i<11;++i)
            {
                for(int j=0;j<2;++j)
                {
                    f_in >> transaction;
                    if(transaction=="}") break;
                    T += transaction;
                    if(j<1) T += " ";
                }
                if(transaction=="}") break;
                *called=All.all[All.vplace];
                called->transactions[i]=T;
                
                transaction="";
                T="";
            }
            ++All.vplace;
        }
        
    }
    return is;
}

ostream& operator<<(ostream& os, Bank& All) //Cout bank.
{
    Customer* called = new Customer("Default","Default",0,1,0);
    
	ofstream f_out("Bank.txt", ofstream::out);
    
    for(int i=0;i<100;++i)
    {
        *called=All.all[i];
        if(called->callbal()!=0)
        {
            f_out << "[ customer " << called->callfn() << ' ' << called->callln() << endl;
            f_out << "  account " << called->callan() << endl;
            f_out << "  PIN " << called->callpin() << endl;
            f_out << "  balance " << called->callbal() << endl;
            f_out << "  transcations { ";
            
            for(int j=1;j<11;++j)
            {
                f_out << called->transactions[j] << ' ';
            }
            
            f_out << " }" << endl;
            f_out << ']' << endl;
        }
    }
            return os;
}
