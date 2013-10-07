#include "variables.h" 

class Statistics
{ 
public: 
	string cust_trans;
}; 

class Customer{ 
	double balance; 
	int position_in_vector; 
	string c_transactions; 
public: 
	void set_balance (double& new_balance);
	void set_position (int& place);
	void set_transactions (string& transac);
	void output_balance (double& o_bal); 
	void output_position (int& o_pos); 
	void output_transactions (string& o_trans); 
};

void Customer::set_balance(double& new_balance){ 
	balance = new_balance;
}

void Customer::set_position(int& place){
	position_in_vector = place;
}

void Customer::set_transactions(string& transac){
	c_transactions = transac; 
}

void Customer::output_balance(double& o_bal){ 
	o_bal = balance; 
} 

void Customer::output_position(int& o_pos){ 
	o_pos = position_in_vector;
} 

void Customer::output_transactions(string& o_trans){ 
	o_trans = c_transactions;
}

class Bank{
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

void Bank::isetup_bank(){ 
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

void Bank::finalize_bank(){	
	ofstream ost(bank_file.c_str()); 
	if (total_num_customers != 0) avg_bal_per_cust = total_bal/total_num_customers; 
	else avg_bal_per_cust = 0; 
	ost<<total_bal<<'\n'<<total_num_customers<<'\n'<<avg_bal_per_cust; 
}

void Bank::Bank_deposit(double money){ 
	total_bal = total_bal + money; 
}

void Bank::add_customer(){ 
	++total_num_customers; 
}

void Bank::delete_customer(){ 
	--total_num_customers; 
}

void Bank::Bank_info(){ 
	if (total_num_customers != 0) avg_bal_per_cust = total_bal/total_num_customers; 
	else avg_bal_per_cust = 0; 
	cout<<"Total Bank balance: $"<<total_bal<<'\n'<<"Total number of customers: "<<total_num_customers<<'\n'
	    <<"Average balance per customer: $"<<avg_bal_per_cust<<endl; 
}
