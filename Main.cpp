#include "Statistics.h"

Account* called = new Account("Default","Default",0,1,0);

void fill(Bank& All) //Fill the bank with default accounts
{
    for(int i=0;i<100;++i)
    {
        All.all[i]=*called;
    }
}

void in(Bank& All) //Write in what is to be stored in Bank
{
    int spot=2;
    int linecount=1;
    int reset=0;
    
    string fname;
    string lname;
    string s_a_number;
    string s_pin;
    string s_balance;
    
    int i_a_number=0;
    int i_pin=0;
    int i_balance=0;
    
    ifstream ifs1("Bank.txt", ifstream::in);
    
    while(true)
    {
        string line;
        
        if(linecount==1) fname="";
        if(linecount==1) lname="";
        if(linecount==2) s_a_number="";
        if(linecount==3) s_pin="";
        if(linecount==4) s_balance="";
        
        if(linecount==1)
        {
            i_a_number=0;
            i_pin=0;
            i_balance=0;
        }
        
        getline(ifs1,line);
        
        if(linecount==6)
        {
            reset=1;
        }
        
        if(linecount==5)
        {
            spot=18;
            for(int i=1;i<11;++i)
            {
                string T="";
                for (spot;spot<line.size(); ++spot)
                {
                    if(line[spot]!=')')
                    {
                        T += line[spot];
                    }
                    else
                    {
                        spot=spot+3;
                        break;
                    }
                }
                *called=All.all[(i_a_number-600000)];
                called->transactions[i]=T;
                if(i==10) ++linecount;
            }
        }
        
        if(linecount==4)
        {
            for (spot=10;spot<line.size(); ++spot)
            {
                s_balance += line[spot];
                if ((spot+1)==(line.size()))
                {
                    istringstream (s_balance) >> i_balance; //Convert string to int
                    Account* A= new Account(fname,lname,i_a_number,i_pin,i_balance);
                    All.all[All.vplace]=*A;
                    ++linecount;
                    ++linecount;
                }
            }
        }
        
        if(linecount==3)
        {
            for (spot=6;spot<line.size(); ++spot)
            {
                s_pin += line[spot];
                if ((spot+1)==(line.size()))
                {
                    istringstream (s_pin) >> i_pin; //Convert string to int
                    ++linecount;
                }
            }
            
        }
        
        if(linecount==2) //Account number
        {
            for(spot=10;spot<line.size(); ++spot)
            {
                s_a_number += line[spot];
                
                if ((spot+1)==(line.size()))
                {
                    istringstream (s_a_number) >> i_a_number; //Convert string to int
                    if((i_a_number-600000)>All.vplace) All.vplace=(i_a_number-600000);
                    if((i_a_number-600000)<All.low && i_a_number!=0) All.low=(i_a_number-600000);
                    All.a_num=i_a_number;
                    ++linecount;
                }
            }
        }
        
        if(linecount==1) //First and last name
        {
            for (spot=11;spot<line.size(); ++spot) //n starts at 11 because the beginning of the first name is 11 characters over.
            {
                if (line[spot]!=' ')
                {
                    fname += line[spot];
                }
                else
                {
                    ++spot;
                    break;
                }
            }
            
            for (;spot<line.size(); ++spot)
            {
                lname += line[spot];
                if ((spot+1)==(line.size()))
                {
                    ++linecount;
                }
            }
            
        }
        
        if(reset==1)
        {
            linecount=1;
            reset=0;
        }
        
        if(ifs1.eof()) break;
        ifs1.clear();
    }
    ++All.vplace;
    ++All.a_num;
}

void out(Bank& All) //Write out what is stored in Bank
{
    ofstream ofs1("Bank.txt", ofstream::out); 
    
    for(int i=All.low;i<All.vplace;++i)
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
    int d=0;
    string fname;
    string lname;
    
    int pin=0;
    
    cout << "Enter your first and last name:\n";
    cin >> fname >> lname;
    
    pin=rand() % 9000 + 1000;
    
    for(int i=1;i<100;++i)
    {
        if(((All.a_num-600000)-i)>0) *called=All.all[((All.a_num-600000)-i)];
        if(called->balance==0 && ((All.a_num-600000)-i)>0)
        {
            Account* A= new Account(fname,lname,All.a_num-i,pin,1000);
            
            cout << "Your account number is " << All.a_num-i << " and your pin number is " << pin << ".\n";
            cout << "Your beginning balance is $1000.\n";
            
            All.all[((All.a_num-600000)-i)]=*A;
            d=1;
            if(All.low>((All.a_num-600000)-i))--All.low;
            break;
        }
    }
    if(d==0)
    {
        Account* A= new Account(fname,lname,All.a_num,pin,1000);
        
        cout << "Your account number is " << All.a_num << " and your pin number is " << pin << ".\n";
        cout << "Your beginning balance is $1000.\n";

        All.all[All.vplace]=*A;
        ++All.vplace && ++All.a_num;
    }

}

void close(Bank& All)
{
    string answer;
    int a_number;
    int pin;
    
    cout << "Are you sure you want to close your account?(yes/no)\n";
    cin >> answer;
    
    if(answer=="yes")
    {
        cout << "Enter your account number: \n";
        cin >> a_number;
        
        cout << "Enter your PIN: \n";
        cin >> pin;
        
        if(600000<a_number)
        {
            *called=All.all[(a_number-600000)];
        
            if(called->pin_number==pin)
            {
                if(called->balance>500) cout << "You have more than $500. Please see cashier to withdraw money.\n";
                else
                {
                    cout << "You have withdrawn: $" << called->balance << '\n';
                    Account* replace = new Account("Default","Default",0,1,0);
                    All.all[(a_number-600000)]= *replace;
                    cout << "Your account has been canceled.\n";
                }
            }
            else cout << "Wrong PIN.\n";
        }
        else cout << "Bad account number.\n";
    }
}

int main()
{
    Bank All;
    fill(All); 
    
    in(All);
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
    if(operation==2) close(All);
    out(All);
}
