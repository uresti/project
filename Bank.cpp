#include "Bank.h"

Customer* called = new Customer("Default","Default",0,1,0); //Default account

void Bank::fill() //Fill the bank with default accounts.
{
    for(int i=0;i<100;++i)
    {
        all[i]=*called;
    }
}

void Bank::create(Statistics& Info) //Create an account with the bank.
{
    string fname;
    string lname;
    
    int pin=0;
    int balance=0;
    int d=0;
    
    cout << "Enter your first and last name:\n";
    cin >> fname >> lname;
    
    srand(time(NULL)); //Randomize 'rand' based on time.
    pin=rand() % 9000 + 1000; //Generate a random number between 1000 and 9999.
    a_num=rand() % 900000 + 100000; //Generate a random account number.
    
    for(int i=0;i<100;++i) //Check to make sure account number is unique.
    {
        if(all[i].callan()==a_num)
        {
            a_num=rand() % 900000 + 100000;
            i=-1;
        }
    }
    
    cout << "You must deposit at least $1000 to open an account.\n";
    cout << "Enter the amount to deposit: $";
    
    cin >> balance;
    
    if((!balance && balance<1000.00) || balance<1000.00) throw runtime_error("Not a valid deposit amount!\n"); //Check to make sure it's a number and greater than 1000.

        Customer* A= new Customer(fname,lname,a_num,pin,balance);
        
        cout << "Your account number is " << a_num << " and your pin number is " << pin << ".\n";
        cout << "Your beginning balance is $" << balance << '\n';
        
        all[vplace]=*A; //Put the account into the bank.
        ++vplace; //Increase the counter of the position in the array.
        Info.stat_deposit(balance); //Increase Total balance.
        Info.tot_deposit(balance); //Increase Total deposit.
        Info.addcustomer();
}

void Bank::close(Statistics& Info) //Close an account with the Bank.
{
    string answer;
    int a_number;
    int pin;
    
    cout << "Are you sure you want to close your account?(yes/no)\n";
    cin >> answer;
    
    if(answer!="yes" && answer!="no") throw runtime_error("Invalid input.\n"); //Check valid response.
    
    if(answer=="yes")
    {
        cout << "Enter your account number: \n";
        cin >> a_number;
        
        if(!a_number || a_number<=99999 || a_number>=1000000) throw runtime_error("Not a valid account number!\n");
        for(int i=0;i<100;++i)
        {
            if(all[i].callan()==a_number)
            {
                a_number=i;
                break;
            }
        }
        
        cout << "Enter your PIN: \n";
        cin >> pin;
        
        if(!pin || pin<=999 || pin>=10000) throw runtime_error("Not a valid pin number!\n");
        
        *called=all[a_number]; //Get the account.
            
        if(called->callpin()==pin)
        {
            if(called->callbal()>500) cout << "You have more than $500. Please see cashier to withdraw money.\n";
            else
            {
                cout << "You have withdrawn: $" << called->callbal() << '\n';
                Info.stat_withdraw(called->callbal());
                Info.subcustomer();
                Customer* replace = new Customer("Default","Default",0,1,0);
                all[a_number]= *replace; //Replace the account with a 'default account' so that it will not be written out to the file.
                cout << "Your account has been canceled.\n";
            }
        }
        else cout << "Wrong PIN.\n";
    }
}

void Bank::withdraw(int a_number,Statistics& Info) //Withdraw money from an account.
{
    time_t t = time(0); //Used to generate the date.
    struct tm * now = localtime( & t );
    
    int pin;
    int closer=0;
    double withdraw;
    
    cout << "Enter your PIN: \n";
    cin >> pin;
    if(!pin || pin<=999 || pin>=10000) throw runtime_error("Invalid pin number!\n");
    
    *called=all[a_number]; //Get the account.
    
    if(called->callpin()==pin)
    {
    	if(called->callbal()<1000) //Check if balance is greater than $1000.
        {
            cout    << "It will cost you $10 to make a withdraw since your funds are less than $1000!\n"
            << "If you wish to incur no charge, please withdraw $0.00!\n";
        }
        else //If not, express the possible chance to incur a fee.
        {
            cout    << "Any withdraw that leaves the account balance below $1000 will incur a $10 fee!\n"
                    << "If you wish to incur no charge, please withdraw $0.00!\n";
        }
        
        cout << "Enter the amount to withdraw: $";
        cin >> withdraw;
        
        if((!withdraw && withdraw<0.00) || withdraw<0.00) throw runtime_error("Not a valid withdraw amount!\n");
        
        if(withdraw>500) throw runtime_error("Can't withdraw more than $500.\n");
        
        if(called->callbal()-withdraw<50 && called->callbal()-withdraw>0) //Used to close an account if withdraw puts it under $50.
        {
            closer=1;
        }
        
        if(called->callbal()-withdraw<1000 && withdraw>=0.001 && called->callbal()-withdraw>0 && closer==0) //Incur charge.
        {
            cout << "After withdraw, your account balance is less than $1000 thus carring out a withdraw has cost you $10.\n";
            called->balwit(10);
            Info.stat_withdraw(10);
        }
        
        if(called->callbal()-withdraw<50 && called->callbal()-withdraw>0) //Ask to close account.
        {
            cout    << "You do not have sufï¬cient funds in your account to maintain it.\n"
                    << "You will be required to close your account\n";
        }
        else if(called->callbal()-withdraw>0)
        {
            called->balwit(withdraw);
            Info.stat_withdraw(withdraw);
            
            stringstream year1; //Converts the 'int' year into a 'string'.
            year1 << (now->tm_year+1900);
            string year(year1.str());
            
            stringstream month1; //Converts the 'int' month into a 'string'.
            month1 << (now->tm_mon+1);
            string month(month1.str());
            
            stringstream day1; //Converts the 'int' day into a 'string'.
            day1 << (now->tm_mday);
            string day(day1.str());
            
            stringstream trans1; //Converts the 'int' withdraw into a 'string'.
            trans1 << (withdraw);
            string trans(trans1.str());
            
            for(int i=10; i>0;--i)
            {
                called->transactions[i]=called->transactions[i-1]; //Moves all the previous transactions over one in the array.
                if(i==1) called->transactions[1]= '(' + year + '-' + month + '-' + day + ' ' + '-' + trans + ')'; //Combines all the strings and stores it in the array.
            }
            
            cout << "Account balance: $" << called->callbal() << '\n';
        }
        else if(called->callbal()-withdraw<0) cout << "Insufficient funds.\n";
        
        all[a_number]=*called; //Put the account back into the bank.
        if(closer==1) close(Info);
    }
    
    else cout << "Wrong PIN.\n";
}

void Bank::deposit(int a_number,Statistics& Info) //Deposit money into an account.
{
    time_t t = time(0); //Used to generate the date.
    struct tm * now = localtime( & t );
    
    int pin;
    double deposit;
    
    cout << "Enter your PIN: \n";
    cin >> pin;
    
    if(!pin || pin<=999 || pin>=10000) throw runtime_error("Invalid pin number!\n");
    
    *called=all[a_number]; //Get the account.
    
    if(called->callpin()==pin)
    {
        cout << "Enter the amount to deposit: $";
        cin >> deposit;
        if((!deposit && deposit<0.00) || deposit<0.00) throw runtime_error("Not a valid deposit amount!\n");
        
        
        called->baldep(deposit);
        Info.stat_deposit(deposit);
        Info.tot_deposit(deposit);
        
        stringstream year1; //Converts the 'int' year into a 'string'.
        year1 << (now->tm_year+1900);
        string year(year1.str());
        
        stringstream month1; //Converts the 'int' month into a 'string'.
        month1 << (now->tm_mon+1);
        string month(month1.str());
        
        stringstream day1; //Converts the 'int' day into a 'string'.
        day1 << (now->tm_mday);
        string day(day1.str());
        
        stringstream trans1; //Converts the 'int' deposit into a 'string'.
        trans1 << (deposit);
        string trans(trans1.str());
        
        for(int i=10; i>0;--i)
        {
            called->transactions[i]=called->transactions[i-1]; //Moves all the previous transactions over one in the array.
            if(i==1) called->transactions[1]= '(' + year + '-' + month + '-' + day + ' ' + trans + ')'; //Combines all the strings and stores it in the array.
        }
        cout << "Account balance: $" << called->callbal() << '\n';
        all[a_number]=*called; //Put the account back into the bank.
    }
    else cout << "Wrong PIN.\n";
}

void Bank::account_balance(int a_number) //Check account balance.
{
    int pin;
    
    cout << "Enter your PIN: \n";
    cin >> pin;
    
    if(!pin || pin<=999 || pin>=10000) throw runtime_error("Invalid pin number!\n");
    
    *called=all[a_number]; //Call the account.
    
    if(called->callpin()==pin)
    {
        cout << "Account balance: $" << called->callbal() << '\n'; //Print out balance.
    }
    else cout << "Wrong PIN.\n";
}

void Bank::transactions(int a_number) //Check last 10 transactions.
{
    int pin;
    
    cout << "Enter your PIN: \n";
    cin >> pin;
    
    if(!pin || pin<=999 || pin>=10000) throw runtime_error("Invalid pin number!\n");
    
    *called=all[a_number]; //Call the account
    
    if(called->callpin()==pin)
    {
        for(int i=1;i<11;++i)
        {
        	if(called->transactions[i]=="") break;
            cout << called->transactions[i] << '\n'; // Print out the last 10 transactions.
        }
    }
    else cout << "Wrong PIN.\n";
}
