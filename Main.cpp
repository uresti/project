#include "Statistics.h"

Customer* called = new Customer("Default","Default",0,1,0);

void fill(Bank& All) //Fill the bank with default accounts
{
    for(int i=0;i<100;++i)
    {
        All.all[i]=*called;
    }
}

void create(Bank& All)
{
    string fname;
    string lname;
    
    int pin=0;
    int d=0;
    
    cout << "Enter your first and last name:\n";
    cin >> fname >> lname;
    
    pin=rand() % 9000 + 1000;
    
    for(int i=1;i<100;++i)
    {
        if(((All.a_num-600000)-i)>0) *called=All.all[((All.a_num-600000)-i)];
        if(called->balance==0 && ((All.a_num-600000)-i)>0)
        {
            Customer* A= new Customer(fname,lname,All.a_num-i,pin,1000);
            
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
        Customer* A= new Customer(fname,lname,All.a_num,pin,1000);
        
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
    
    if(answer!="yes" && answer!="no") throw runtime_error("Invalid input.\n");
    
    if(answer=="yes")
    {
        cout << "Enter your account number: \n";
        cin >> a_number;
        
        if(!a_number) throw runtime_error("Not a valid account number!\n");
        
        cout << "Enter your PIN: \n";
        cin >> pin;
        
        if(!pin) throw runtime_error("Not a valid pin number!\n");
        
        if(600000<=a_number && a_number<=All.a_num)
        {
            *called=All.all[(a_number-600000)];
        
            if(called->pin_number==pin)
            {
                if(called->balance>500) cout << "You have more than $500. Please see cashier to withdraw money.\n";
                else
                {
                    cout << "You have withdrawn: $" << called->balance << '\n';
                    Customer* replace = new Customer("Default","Default",0,1,0);
                    All.all[(a_number-600000)]= *replace;
                    cout << "Your account has been canceled.\n";
                }
            }
            else cout << "Wrong PIN.\n";
        }
        else cout << "Bad account number.\n";
    }
}

void withdraw(Bank& All,int a_number)
{
    time_t t = time(0);
    struct tm * now = localtime( & t );
    
    int pin;
    double withdraw;
    
    cout << "Enter your PIN: \n";
    cin >> pin;
    if(!pin) throw runtime_error("Invalid pin number!\n");
    
    *called=All.all[(a_number-600000)];

    if(called->pin_number==pin)
    {
        if(called->balance<50) cout << "You do not have sufﬁcient amount of money in your account to maintain it.\n";
        if(called->balance<1000)
        {
            cout    << "It will cost you $10 to make a withdraw since your funds are less than $1000!\n"
                    << "If you wish to incur no charge, please withdraw $0.00!\n";
        }
        
        
        cout << "Enter the amount to withdraw: $";
        cin >> withdraw;
        if(!withdraw) throw runtime_error("Not a valid withdraw amount!\n");
        
        if(called->balance<1000 && withdraw>=0.001)
        {
            cout << "Your funds are less than $1000 thus carring out a withdraw has cost you $10.\n";
            called->balance=called->balance-10;
        }
        
        if(called->balance-withdraw>0 && withdraw<=500)
        {
            called->balance=called->balance-withdraw;
            
            stringstream year1;
            year1 << (now->tm_year+1900);
            string year(year1.str());
            
            stringstream month1;
            month1 << (now->tm_mon+1);
            string month(month1.str());
            
            stringstream day1;
            day1 << (now->tm_mday);
            string day(day1.str());
            
            stringstream trans1;
            trans1 << (withdraw);
            string trans(trans1.str());
            
            for(int i=10; i>0;--i)
            {
                called->transactions[i]=called->transactions[i-1];
                if(i==1) called->transactions[1]= '(' + year + '-' + month + '-' + day + ' ' + "Withdraw $" + trans + ')';
            }
        }
        else if(called->balance-withdraw<0) cout << "Insufficient funds.\n";
        else cout << "Can't withdraw more than $500.\n";
        
        All.all[(a_number-600000)]=*called;
    }
    else cout << "Wrong PIN.\n";
}

int main()
{
    Bank All;
    fill(All);

	try{
            cin >> All;
            cout << "This is your Piggy Bank. Welcome valued customer!\n";
            int accountnumber=0;
            int accountenter=0;
            string answer="yes";
       
            while(answer=="yes")
            {
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
                
                if(!operation) throw runtime_error("Not a valid selection!\n");
                if(operation<1 || operation>7) throw runtime_error("Not a valid selection!\n");
		
                if(operation==1) create(All);
                if(operation==2) close(All);
            
                else if(accountenter==0 && operation!=1 && operation!=2)
                {
                    cout << "Enter your account number: \n";
                    cin >> accountnumber;
                    if(!accountnumber || accountnumber<=600000 || accountnumber>=All.a_num) throw runtime_error("Not a valid account number!\n");
                    ++accountenter;
                }
                
                if(operation==3) withdraw(All,accountnumber);
                
                cout << "Does you wish to carry out another action?(yes/no)\n";
                cin >> answer;
                if(answer!="yes" && answer!="no") throw runtime_error("Invalid input.\n");
                if(answer=="no") break;
            }
            cout << All;
            cout << "Thank you!\n";
	}
	
	catch (exception& e)
    	{
        	cout << All;
		cerr << "Oops! " << e.what() << '\n'; 
		return 1;
	}
	catch (...)
    	{
        	cout << All;
		cerr << "Oops: unknown exception!\n"; 
		return 2;
	}
}
