#include "Bank.h"

class Statistics
{
	double total_bal;
	int total_num_customers; 
	double avg_bal_per_cust;
public:
	void isetup_bank();
	void finalize_bank(); 
	void Bank_deposit(double money); 
	void delete_customer();
	void add_customer(); 
	void Bank_info();

};

void Statistics::isetup_bank(){ 
	ifstream ibank(bank_file.c_str()); 
	string temp_input; 
	while(ibank>>temp_input){ 
		bank_info.push_back(temp_input); 
	}
	string temp = bank_info[0]; 
	stringstream convert; 
	convert<<temp; 
	convert>>total_bal; 

	temp = bank_info[1]; 
	stringstream convert1; 
	convert1<<temp; 
	convert1>>total_num_customers; 
	
	temp = bank_info[2]; 
	stringstream convert2;
	convert2<<temp; 
	convert2>>avg_bal_per_cust;
}

void Statistics::finalize_bank(){	
	ofstream ost(bank_file.c_str()); 
	if (total_num_customers != 0) avg_bal_per_cust = total_bal/total_num_customers; 
	else avg_bal_per_cust = 0; 
	ost<<total_bal<<'\n'<<total_num_customers<<'\n'<<avg_bal_per_cust; 
}

void Statistics::Bank_deposit(double money){ 
	total_bal = total_bal + money; 
}

void Statistics::add_customer(){ 
	++total_num_customers; 
}

void Statistics::delete_customer(){ 
	--total_num_customers; 
}

void Statistics::Bank_info(){ 
	if (total_num_customers != 0) avg_bal_per_cust = total_bal/total_num_customers; 
	else avg_bal_per_cust = 0; 
	cout<<"Total Bank balance: $"<<total_bal<<'\n'<<"Total number of customers: "<<total_num_customers<<'\n'
	    <<"Average balance per customer: $"<<avg_bal_per_cust<<endl; 
}
