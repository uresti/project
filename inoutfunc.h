#include "classes.h" 

// func starts program's info by assigning 
// values stored in files and assigning them to variables (variables.h)
void Bank_info_start(Bank& Main)
{
	string read_names;
	ifstream name_get(names_file.c_str()); 
	
	while(name_get>>read_names)
	{
		account_names.push_back(read_names);
	}
	name_get.close();
	number_of_accounts = account_names.size();
	
	int read_account_num;
	ifstream acc_num_get(accounts_file.c_str());
	
	while(acc_num_get>>read_account_num)	
	{
		if (read_account_num != 0) all_account_num.push_back(read_account_num);
		else break;
	}
	acc_num_get.close();
	
	int read_pin;
	ifstream pins_get(pins_file.c_str());
	
	while(pins_get>>read_pin) 
	{
		if (read_pin != 0) all_pins.push_back(read_pin);
		else break;
	}
	
	
	
	pins_get.close();
	Main.isetup_bank();
}

//func saves changes made to customers, either closing/opening accounts 
//the modifies the amount of customers and their corresponding info in files

void Bank_info_end(Bank& Main) 
{ 
	int count = account_names.size(); 
	for (count; count < 30; ++count) account_names.push_back(" "); 
	
	ofstream end_names(names_file.c_str());
	for (int i = 0; i < account_names.size (); ++i) 
	{
		end_names << account_names[i] << endl; 
	}
	end_names.close();
	
	count = all_account_num.size();
	for (count; count < 30; ++count) all_account_num.push_back(0);
	ofstream end_accounts(accounts_file.c_str());
	for (int i = 0; i < account_names.size(); ++i) 
	{
		end_accounts << all_account_num[i] << endl; 
	}
	end_accounts.close();
	
	count = all_pins.size(); 
	for (count; count < 30; ++count) all_pins.push_back(0);
	ofstream end_pins(pins_file.c_str()); 
	for (int i = 0; i < account_names.size(); ++i) 
	{
		end_pins << all_pins[i] << endl;
	}
	end_pins.close(); 
	Main.finalize_bank();
}

//Time stamp function creates the timestamp required to log the transactions 
//puts the transactions in a format that could easily be used by the ofstreams
void time_stamp(double val, string& trans)
{
	time_t t = time(0);
	struct tm * now = localtime ( & t); 
	
	int year = ((now->tm_year +1900))-2000;
	int month = (now->tm_mon +1);
	int day = (now->tm_mday);
	
	string change = "0"; 
	stringstream conv; 
	conv<<val; 
	conv>>change; 
	
	vector<string>transactions;
	string temp = "0";
	stringstream convert; 
	convert<<trans;
	
	while(convert>>temp) 
	{
		transactions.push_back(temp);
	}
	
	string value_year = "0";
	stringstream ss;
	ss<<year;
	ss>>value_year;
	
	string value_month = "0";
	stringstream ss1;
	ss1<<month; 
	ss1>>value_month;
	
	string value_day = "0";
	stringstream ss2; 
	ss2<<day;
	ss2>>value_day; 
	
	vector<string>final_trans(11);
	
	final_trans[1] = "{" + value_month + "/" + value_day + "/" + value_year + "__$" + change + "}";
	final_trans[0] = transactions [0]; 
	
	for (int i = 2; i<11; ++i) 
	{
		final_trans[i] = transactions [i-1];
	}
	
	trans = final_trans[0] + " " + final_trans[1] + " " + final_trans[2] + " " + final_trans[3] + " " + final_trans[4] + " " + final_trans[5] + " " + final_trans[6] + " " + final_trans[7] + " " + final_trans[8] + " " + final_trans[9] + " " + final_trans[10];
}

//makes sure intial deposti when opening account is more than 1000 dollars
void check_init_deposit(double& start_money)
{
	while(true) 
	{
		if (start_money < 1000) 
		{
			cout<<"You  can only start an account with a minimum of $1000 dollars!"<<endl;
			cout<<"Please enter more money"<<endl;
		}
		else break; 
	}
}

//Opens new account by creating a customer file with information of account 
//includes randome generated pins and account numbers, and balances, trans, and names.
void Open_new_account (Bank& Main) 
{
	if (all_account_num.size() < 30) 
	{
		double initial_cash = 0;
		string last_name;
		string first_name;
		int iterate = 1; 
		if (all_account_num.size() != 0) iterate = all_account_num.size();
		
		int account_num;
		int PIN;
		
		cout<<"To create account please enter first and last name."<<endl;
		cin>>first_name>>last_name;
		cout<<"Please Enter you initial moentary deposit!"<<endl;
		cin>>initial_cash;
		check_init_deposit(initial_cash); 
		Main.Bank_deposit(initial_cash); 
		string file_name = first_name + " " + last_name + ".txt";
		account_names.push_back(file_name); 
		ofstream ost(file_name.c_str()); 
		srand(time(0));
		for(iterate; iterate>0; --iterate) 
		{
			account_num = rand () % 10000 +  50000;
			PIN = rand() % 1000 + 8999;
		}
		all_account_num.push_back(account_num);
		all_pins.push_back(PIN);
		
		time_t t = time(0);
		struct tm * now = localtime (  & t);
		
		int year = ((now->tm_year +1900))-2000;
		int month = (now->tm_mon +1);
		int day = (now->tm_mday); 
		
		string change = "0";
		stringstream conv;
		conv<<initial_cash;
		conv>>change;
		
		string value_year = "0"; 
		stringstream ss;
		ss<<year;
		ss>>value_year;
		
		string value_month = "0";
		stringstream ss1;
		ss1<<month;
		ss1>>value_month;
		
		string value_day = "0"; 
		stringstream ss2;
		ss2<<day;
		ss2>>value_day;
		
		string first;
		first = "{" + value_month + "/" + value_day + "/" + value_year + "__$" + change + "}";
		
		cout<< "Your new account number is: "<<account_num<<endl;
		cout<< "Your new PIN is:" <<PIN<<endl;
		cout<< "Please be aware a 10 dollar fee will be applied if your account balance is less than $1000" <<endl; 
		ost<< "Customer: "<<first_name<<' '<<last_name<<endl;
		ost<< "Account: "<<account_num<<endl;
		ost<< "PIN: "<<PIN<<endl;
		ost<< "Balance: "<<initial_cash<<endl;
		ost<< "Transactions: "<<first<<" 0 0 0 0 0 0 0 0 0"; 
		ost.close(); 
		Main.add_customer(); 
	} 
	else cout<<"Too many accounts in Bank. Account can't be made"<<endl;
}

//function closes an account by deleting all contents of that customer
// updates files to remove info
void Close_account(Bank& Main) 
{
	finalize = false;
	string too_be = "no";
	cout<<"Are you sure you want to close your account? "<<endl;
	cin>>too_be;
	if (too_be == "yes"||too_be == "Yes") 
	{
		int check = 0;
		int customer = 0;
		bool correct_pin = false;
		int i = 0;
		    while (correct_pin == false) 
			{
				cout<<"Enter Account Number"<<endl;
				i = 0; 
				cin>>check;
				while (i < all_account_num.size()) 
				{
					if (check == all_account_num[i])
					{	
						customer = i;
						correct_pin = true;
						break;
					}
					++i;
				}
				if (i == all_account_num.size()) 
				{
					cout<<endl<<"Incorrect Account Number."<<endl;
				}
			}
			correct_pin = false;
			while (correct_pin == false)
			{ 
				cout<<"Please enter Pin"<<endl;
				cin>>check;
				
				if (check == all_pins[i])
				{
					correct_pin = true; 
					break;
				}
				
				else 
				{
					cout<<endl<<"Incorrect Pin."<<endl;
				}
			}
			
			vector<string>temp_cust;
			string customer_file = account_names[i];
			ifstream cust(customer_file.c_str());
			string temp input;
			while(cust>>temp_input)
			{
				temp_cust.push_back(temp_input);
			}
			string temp = temp_cust[8];
			stringstream convert;
			conver<<temp;
			double bal = 0;
			convert>>bal;
			if (bal>500)
			{
				cout<<"You can only recieve $500 through this machine."<<endl;
				cout<<"Please see the cashier for the rest of your money."<<endl;
			}
			bal = 0 - bal;
			Main.Bank_deposit(bal);
			Main.delete_customer();
			cust.close();
			cout<<"You have just closed you account!"<<endl;
			cout<<"Thank you for banking with us!"<<endl;
			
			string delete_name;
			delete_name = account_names[i]; 
			remove(delete_name.c_str());
			all_account_num.erase(all_account_num.begin()+i);
			all_pins.erase(all_pins.begin()+i);
			account_names.erase(account_names.begin()+i);
	}
		
		else cout<<"You did not close your account."<<endl;
}

//saves any changes of a customer's info to corresponding files
void finalize_customer(Customer& blank, double& new_bal, int& pos, string& transaction) 
{
	if(finalize == true)
	{
		blank.output_balance(new_bal);
		blank.output_position(pos);
		string file_name = account_names[pos];
		cout<<"Your balance at closing is: $"<<new_bal<<" today"<<endl;
		ostringstream convert;
		convert<<new_bal;
		
		string temp = convert.str();
		
		customer_files[8] = temp;
		ofstream ost(file_name.c_str());
		ost<<customer_files[0] +' '+ customer_files[1] + ' ' + customer_files[2]<<endl; 
		   <<customer_files[3] +' '+ customer_files[4]<<endl;
		   <<customer_files[5] +' '+ customer_files[6]<<endl;
	       <<customer_files[7] +' '+ customer_files[8]<<endl;
		   <<transaction<<endl;
		ost.close();
	}
	else if (finalize == false) cout<<"Your account has been closed!"<<endl;
}

//checks to make sure that users cannot withdraw more than lower limit of $50
//give them option of closing their account if thw want to withdraw more than limit allows. 

void Withdraw_check(Bank& Main, Customer& user, double& money_withdrawn)
{
	finalize = true;
	double temp_val = 0.0;
	int choice = 0;
	user.output_balance(temp_val);
	
	temp_val = temp_val - money_withdrawn;
	while (temp_val<50 && choice != 2) 
	{
		cout<<"Please withdraw less money. You will have less than $50.00 dollars."<<endl;
		cout<<"Or you don't have enough funds. Or you can also close the account and get funds."<<endl;
		cout<<"Input \"1\" to withdraw less money and input \"2\" to close accoutn."<<endl;
			while(choice < 1 || choice > 2)
			{
				cin>>choice;
				if (choice == 1)
				{
					cout<<"Please enter another amount to be withdrawn"<<endl;
					cin>>money_withdrawn;
					user.output_balance(temp_val);
					temp_val = temp_val - money_withdrawn;
				}
				else if (choice == 2)
				{
					cout<<"You will get the funds from your account."<<endl;
					Close_account(Main);
				}
			}
	}
		
	if (choice != 2) 
	{
		money_withdrawn = 0 - money_withdrawn;
		Main.Bank_deposit (money_withdrawn);
	}
	user.set_balance(temp.val);
}

//function changes the values of customer's files if they choose to withdraw
//runs withdraw check and runs timestamp func to create a new transantion.
void Withdraw (int i, Bank& Main, Customer& user, string& trans)
{
	int check = 0;
	int cust = 0;
	bool correct_pin = false;
	double amount; 
	
	while (correct_pin == false) 
	{
		cout<<"Please enter Account Number"<<endl; 
		cin>>check;
		while (check != all_account_num[i])
		{
			cout<<"Incorrect Account Number."<<endl;
			cout<<"Please input correct account number."<<endl; 
			cin>>check;
		}
		correct_pin = true;
	}
	
	cust = all_pins[i]; 
	check = 0;
	while (check != cust) 
	{
		cout<<"Please enter Pin again for safety reasons."endl;
		cin>>check;
		if (check == cust)
		{
			cout<<"Please input amount you want to withdraw"<<endl;
			cin>>amount;
			while (amount> 500)
			{
				cout<<"Please enter amount.You can only withdraw less than $500."<<endl; 
				cin>>amount;
			}
			Withdraw_check(Main, user, amount);
			break;
		}
	}
	
	time_stamp(amount, trans);
}
