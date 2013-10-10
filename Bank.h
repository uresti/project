#include "Customer.h"

class Bank
{
public:
    int vplace; //Vector placement
    int a_num; //Account number
    int low;

    Customer* all;
    
    Bank()
    : all(new Customer[100]),vplace(1),a_num(600001),low(100){}
};


istream& operator>>(istream& is, Bank& All)
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
        
        if(next=="customer")
        {
            f_in >> first;
            f_in >> last;
        }
        if(next=="account")
        {
            f_in >> account;
            if((account-600000)>All.vplace) All.vplace=(account-600000);
            if((account-600000)<All.low && account!=0) All.low=(account-600000);
            All.a_num=account;
        }
        if(next=="PIN")
        {
            f_in >> pin;
        }
        if(next=="balance")
        {
            f_in >> balance;
            Customer* A= new Customer(first,last,account,pin,balance);
            All.all[All.vplace]=*A;
        }
        if(next=="{")
        {
            for(int i=1;i<11;++i)
            {
                for(int j=0;j<3;++j)
                {
                    f_in >> transaction;
                    if(transaction=="}") break;
                    T += transaction;
                    if(j<2) T += " ";
                }
                if(transaction=="}") break;
                *called=All.all[(account-600000)];
                called->transactions[i]=T;
                
                transaction="";
                T="";
            }
        }
   
    }
    ++All.vplace;
    ++All.a_num;
    return is;
}

ostream& operator<<(ostream& os, Bank& All)
{
    Customer* called = new Customer("Default","Default",0,1,0);
    
	ofstream f_out("Bank.txt", ofstream::out);
    
    for(int i=All.low;i<All.vplace;++i)
    {
        *called=All.all[i];
        if(called->balance!=0)
        {
            f_out << "[ customer " << called->first_name << ' ' << called->last_name << endl;
            f_out << "  account " << called->account_number << endl;
            f_out << "  PIN " << called->pin_number << endl;
            f_out << "  balance " << called->balance << endl;
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
