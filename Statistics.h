#include "Customer.h"

class Statistics
{
    double total_bal;
	int total_num_customers;
	double total_deposit;
public:
    Statistics(double bal, int customers, double totaldepo)
    :total_bal(bal), total_num_customers(customers), total_deposit(totaldepo) {};
    
    Statistics() {};
    
    void isetup_stat();
	void finalize_stat();
    
	int total_customers() {return total_num_customers;};
	double total_deposits(){return total_deposit;};
	double average_money(){return total_bal/total_num_customers;};
    
    void stat_deposit(double money) {total_bal=total_bal+money;}; //Add to total balance.
    void stat_withdraw(double money) {total_bal=total_bal-money;}; //Subtract from total balance.
    
    void tot_deposit(double money) {total_deposit=total_deposit+money;}; //Add to total deposit.
    
    void addcustomer() {++total_num_customers;};
    void subcustomer() {--total_num_customers;};
    
	void info();
};
