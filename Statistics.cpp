#include "Statistics.h"

vector<string>stat_info;
string stat_file = "Stats.txt";

void Statistics::isetup_stat()
{
	ifstream istat(stat_file.c_str());
	string temp_input;
	while(istat>>temp_input)
    {
		stat_info.push_back(temp_input);
	}
	string temp = stat_info[0]; //Get total balance.
	stringstream convert;
	convert<<temp;
	convert>>total_bal;
    
	temp = stat_info[1]; //Get total number of customers.
	stringstream convert1;
	convert1<<temp;
	convert1>>total_num_customers;
	
	temp = stat_info[2]; //Get total_deposit.
	stringstream convert2;
	convert2<<temp;
	convert2>>total_deposit;
}

void Statistics::finalize_stat()
{
	ofstream ost(stat_file.c_str());
	ost<< total_bal << '\n' << total_num_customers << '\n' << total_deposit;
}

void Statistics::info()
{
    cout << "Please select one of these operations (enter a number): \n";
	cout << "1. Total number of customers." << endl;
	cout << "2. Total amount of deposits." << endl;
	cout << "3. Average current balance." << endl;
	int swag=0;
	cin >> swag;
    
	switch(swag) {
		case 1:
			cout << "Total number of customers: " << total_customers() << '\n';
			break;
		case 2:
			cout << "Total amount of deposits: $" << total_deposits() << '\n';
			break;
		case 3:
			cout << "Average balance: $" << average_money() << '\n';
			break;
		default:
			cout << "Nope." << endl;
	}
}
