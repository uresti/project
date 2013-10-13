#include "inoutfunc.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std; 

void menu()
{
	system("clear");
	int menu_num = 0;
	
	cout<<"This is your Piggy Bank. Welcome valued customer!"<<endl;
	
	cout<<"1. Open Account"<<endl;
	cout<<"2. Close the Existing Account"<<endl; 
	cout<<"3. Withdraw Money (Max of $500)"<<endl;
	cout<<"4. Deposit Money"<<endl;
	cout<<"5. Account Balance"<<endl;
	cout<<"6. List last 10 transactions"<<endl;
	cout<<"7. Statistical Information"<<endl;
	
	cout<<"Select Operation"<<endl<<endl; 
	cin>>menu_num;
	
	Bank Main;
	Customer me;
	Statistics mine;
	double bal = 0;
	int posi = 0; 
	string transact;
	Bank_info_start(Main);
	
	switch(menu_num)
	{ 
		case 1: 
			Open_new_account (Main);
			break;
		case 2: 
			Close_account(Main);
			break;
		case 3: 
			Setup_customer(me, bal, posi, transact);
			Withdraw(posi, Main, me, transact);
			finalize_customer(me, bal, posi, transact);
			break;
		case 4: 
			Setup_customer(me, bal, posi, transact); 
			Deposit(posi, Main, me, transact);
			finalize_customer(me, bal, posi, transact); 
			break;
		case 5 :
		    View_account_balance(me, bal, posi, transact); 
			break; 
		case 6:
			Setup_customer(me, bal, posi, transact);
			mine.cust_trans = transact;
			cout<<mine.cust_trans<<endl;
			finalize_customer(me, bal, posi, transact); 
			break;
		case 7:
			Statistical_Information (Main);
			break;
			
		}
		Bank_info_end(Main); 
	}
	
int main()
{
	menu();
	return 0; 
}
