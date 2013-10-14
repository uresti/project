/*********************
 Project#1 CSCE 113-502
 
Seegers, Mark
Login name: mseegers
 
Uresti, Reynaldo
Login name: uresti
 *********************/
/*
 The program is designed to be a bank,however, it is more likely to serve the purpose of an ATM. It allows you to create an account,to close that account,withdraw,deposit,check balance, and check the last 10 transactions. You can also check the statistical info about the bank.*/

#include "Bank_cin_cout.h"

int main()
{
    Bank All; //Make the bank and fill it.
    All.fill();
    
    Statistics Info; //Make stats and get info.
    Info.isetup_stat();
    
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
		
                if(operation==1) All.create(Info);
                if(operation==2) All.close(Info);
                if(operation==7) Info.info();
            
                else if(accountenter==0 && operation!=1 && operation!=2) //Find the account in the array!
                {
                    cout << "Enter your account number: \n";
                    cin >> accountnumber;
                    if(!accountnumber || accountnumber<=99999 || accountnumber>=1000000) throw runtime_error("Not a valid account number!\n");
                    for(int i=0;i<100;++i)
                    {
                        if(All.all[i].callan()==accountnumber)
                        {
                            accountnumber=i;
                            break;
                        }
                    }
                    ++accountenter;
                }
                
                if(operation==3) All.withdraw(accountnumber,Info);
                if(operation==4) All.deposit(accountnumber,Info);
                if(operation==5) All.account_balance(accountnumber);
                if(operation==6) All.transactions(accountnumber);
                            
                cout << "Does you wish to carry out another action?(yes/no)\n";
                cin >> answer;
                if(answer!="yes" && answer!="no") throw runtime_error("Invalid input.\n");
                if(answer=="no") break;
            }
            cout << All; //Read out bank info to file.
            Info.finalize_stat();
            cout << "Thank you!\n";
	}
	
	catch (exception& e)
    {
        cout << All;
        Info.finalize_stat();
		cerr << "Oops! " << e.what() << '\n'; 
		return 1;
	}
	catch (...)
    {
        cout << All;
        Info.finalize_stat();
		cerr << "Oops: unknown exception!\n"; 
		return 2;
	}
}
