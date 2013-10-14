#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

class Customer
{
    int pin_number;
    int account_number;
    double balance;
    string first_name;
    string last_name;

public:
    string* transactions;

    int callpin() {return pin_number;};
    int callan() {return account_number;};
    string callfn() {return first_name;};
    string callln() {return last_name;};
    double callbal() {return balance;};
    
    void balwit(double withdraw) {balance=balance-withdraw;}; //Withdraw
    void baldep(double deposit) {balance=balance+deposit;}; //Deposit
	
	
	Customer(const string& f,const string& l ,const int a, const int p, double bal)
    		: first_name(f), last_name(l), account_number(a), pin_number(p), balance(bal), transactions(new string [11]) {};

    Customer() {};
};
