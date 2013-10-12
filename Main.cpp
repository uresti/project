#include "Statistics.h"

Customer* called = new Customer("Default","Default",0,1,0); //Default account

void fill(Bank& All) //Fill the bank with default accounts.
{
    for(int i=0;i<100;++i)
    {
        All.all[i]=*called;
    }
}

void create(Bank& All) //Create an account with the bank.
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
    
    cout << "You must deposit at least $1000 to open an account.\n";
    cout << "Enter the amount to deposit: $";
    
    cin >> balance;
    
    if((!balance && balance<1000.00) || balance<1000.00) throw runtime_error("Not a valid deposit amount!\n"); //Check to make sure it's a number and greater than 1000.
    
    for(int i=1;i<100;++i) //The purpose of this 'for loop' is to fill spots in the Bank array before the latest account. This deals with the case that an account has been closed.
    {
        if(((All.a_num-600000)-i)>0) *called=All.all[((All.a_num-600000)-i)]; //Set 'default' account equal to one less than the latest account.
        if(called->called->callbal()==0 && ((All.a_num-600000)-i)>0)
        {
            Customer* A= new Customer(fname,lname,All.a_num-i,pin,balance);
            
            cout << "Your account number is " << All.a_num-i << " and your pin number is " << pin << ".\n";
            cout << "Your beginning balance is $" << balance << '\n';
            
            All.all[((All.a_num-600000)-i)]=*A; //Put the account into the bank.
            d=1;
            if(All.low>((All.a_num-600000)-i))--All.low; //If needed, then decrease the counter for the lowest position in the array.
            break;
        }
    }
    if(d==0) //If all the spots have been filled before the latest account, then create one after the latest account (in the array).
    {
        Customer* A= new Customer(fname,lname,All.a_num,pin,balance);
        
        cout << "Your account number is " << All.a_num << " and your pin number is " << pin << ".\n";
        cout << "Your beginning balance is $" << balance << '\n';

        All.all[All.vplace]=*A; //Put the account into the bank.
        ++All.vplace && ++All.a_num; //Increase the counter of the position in the array and increase the account number.
    }
}

void close(Bank& All) //Close an account with the Bank.
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
        
        if(!a_number || a_number<=600000 || a_number>=All.a_num) throw runtime_error("Not a valid account number!\n");
        
        cout << "Enter your PIN: \n";
        cin >> pin;
        
        if(!pin || pin<=999 || pin>=10000) throw runtime_error("Not a valid pin number!\n");
        
        if(600000<=a_number && a_number<=All.a_num)
        {
            *called=All.all[(a_number-600000)]; //Get the account.
        
            if(called->callpin()==pin)
            {
                if(called->callpin()>500) cout << "You have more than $500. Please see cashier to withdraw money.\n";
                else
                {
                    cout << "You have withdrawn: $" << called->callbal() << '\n';
                    Customer* replace = new Customer("Default","Default",0,1,0);
                    All.all[(a_number-600000)]= *replace; //Replace the account with a 'default account' so that it will not be written out to the file.
                    cout << "Your account has been canceled.\n";
                }
            }
            else cout << "Wrong PIN.\n";
        }
        else cout << "Bad account number.\n";
    }
}

void withdraw(Bank& All,int a_number) //Withdraw money from an account.
{
    time_t t = time(0); //Used to generate the date.
    struct tm * now = localtime( & t );
    
    int pin;
    int closer=0;
    double withdraw;
    
    cout << "Enter your PIN: \n";
    cin >> pin;
    if(!pin || pin<=999 || pin>=10000) throw runtime_error("Invalid pin number!\n");
    
    *called=All.all[(a_number-600000)]; //Get the account.

    if(called->callpin()==pin)
    {
    	if(called->callbal()<1000)
        {
            cout    << "It will cost you $10 to make a withdraw since your funds are less than $1000!\n"
                    << "If you wish to incur no charge, please withdraw $0.00!\n";
        }
        else
        {
            cout    << "Any withdraw that leaves the account balance below $1000 will incur a $10 fee!\n"
                    << "If you wish to incur no charge, please withdraw $0.00!\n";
        }
        
        cout << "Enter the amount to withdraw: $";
        cin >> withdraw;
        if((!withdraw && withdraw<0.00) || withdraw<0.00) throw runtime_error("Not a valid withdraw amount!\n");
        
        if(called->callbal()-withdraw<50)
        {
            closer=1;
        }

        if(called->callbal()-withdraw<1000 && withdraw>=0.001 && closer==0)
        {
            cout << "After withdraw, your account balance is less than $1000 thus carring out a withdraw has cost you $10.\n";
            called->balwit(10);
        }
        
        if(called->callbal()-withdraw<50)
        {
            cout    << "You do not have sufﬁcient funds in your account to maintain it.\n"
                    << "You will be required to close your account\n";
        }
        else if(called->callbal()-withdraw>0 && withdraw<=500)
        {
            called->balwit(withdraw);
            
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
                if(i==1) called->transactions[1]= '(' + year + '-' + month + '-' + day + ' ' + "Withdraw $" + trans + ')'; //Combines all the strings and stores it in the array.
            }
            cout << "Account balance: $" << called->callbal() << '\n';
        }
        else if(called->callbal()-withdraw<0) cout << "Insufficient funds.\n";
        else cout << "Can't withdraw more than $500.\n";
        
        All.all[(a_number-600000)]=*called; //Put the account back into the bank.
        if(closer==1) close(All);
    }
    else cout << "Wrong PIN.\n";
}

void deposit(Bank& All,int a_number) //Deposit money into an account.
{
    time_t t = time(0); //Used to generate the date.
    struct tm * now = localtime( & t );
    
    int pin;
    double deposit;
    
    cout << "Enter your PIN: \n";
    cin >> pin;
    if(!pin || pin<=999 || pin>=10000) throw runtime_error("Invalid pin number!\n");
    
    *called=All.all[(a_number-600000)]; //Get the account.
    
    if(called->callpin()==pin)
    {
        cout << "Enter the amount to deposit: $";
        cin >> deposit;
        if((!deposit && deposit<0.00) || deposit<0.00) throw runtime_error("Not a valid deposit amount!\n");
        

        called->baldep(deposit);
            
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
            if(i==1) called->transactions[1]= '(' + year + '-' + month + '-' + day + ' ' + "Deposit $" + trans + ')'; //Combines all the strings and stores it in the array.
        }
        cout << "Account balance: $" << called->callbal() << '\n';
        All.all[(a_number-600000)]=*called; //Put the account back into the bank.
    }
    else cout << "Wrong PIN.\n";
}

void account_balance(Bank& All,int a_number) //Check account balance.
{
    int pin;

    cout << "Enter your PIN: \n";
    cin >> pin;
    if(!pin || pin<=999 || pin>=10000) throw runtime_error("Invalid pin number!\n");
    
     *called=All.all[(a_number-600000)]; //Call the account.
    
    if(called->callpin()==pin)
    {
        cout << "Account balance: $" << called->callbal() << '\n'; //Print out balance.
    }
    else cout << "Wrong PIN.\n";
}

void transactions(Bank& All,int a_number) //Check last 10 transactions.
{
    int pin;
    
    cout << "Enter your PIN: \n";
    cin >> pin;
    if(!pin || pin<=999 || pin>=10000) throw runtime_error("Invalid pin number!\n");
    
    *called=All.all[(a_number-600000)]; //Call the account
    
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

//----------------------------------------------------------------------------------------
void Statistics::history()
{
	cout<<"Enter you account number."<<endl;
	int n=1;
	int acc_input,pin_input;
	int acc_num=1;
	int pin_num=5;
	vector<string>trans (10000, "yolo");
	cin >> acc_input;
	
	for (int i=0; i<=n; ++i) 
	{
		if (i==n) 
		{
			cout<< "Not a valid account number."<<endl;
			break;
		}
		if (acc_input==acc_num) {
			cout << "Please enter your pin number." << endl;
			cin >> pin_input;
			int j=0;
			while (pin_input!=pin_num) {
				cout << "Incorrect pin number, try again." << endl;
				cin >> pin_input;
				j++;
				if(j>3) {
					cout << "Exceeded attempt limit(5), exiting." << endl;
					break;
				}
			}
			if(pin_input==pin_num) {
				cout << "Correct. Here is a list of your last 10 transactions: ";
				for(int q=0; q<10; q++) {
					cout << trans.at(q) << '\n';
					
				}
				cout << endl;
			}
			break;
		}
	}
}


void Statistics::info() {	//would normally look in file and do math to the values to find the separate things
	cout << "1. Total number of customers." << endl;
	cout << "2. Total amount of deposits." << endl;
	cout << "3. Average current balance." << endl;
	int swag=0;
	cin >> swag;

	switch(swag) {
		case 1:
			total_customers();
			break;
		case 2:
			total_money();
			break;
		case 3:
			average_money();
			break;
		default:
			cout << "Nope." << endl;
	}
}
//--------------------------------------------------------------------------------------------------	

int main()
{
    Bank All; //Make the bank and fill it.
    fill(All);

	try{
            cin >> All; //Read in bank info from file.
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
                if(operation==4) deposit(All,accountnumber);
                if(operation==5) account_balance(All,accountnumber);
                if(operation==6) transactions(All,accountnumber);
                if(operation==7) Statistics(All);//--------------------------------------
                
                
                cout << "Does you wish to carry out another action?(yes/no)\n";
                cin >> answer;
                if(answer!="yes" && answer!="no") throw runtime_error("Invalid input.\n");
                if(answer=="no") break;
            }
            cout << All; //Read out bank info to file.
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
