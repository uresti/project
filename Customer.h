#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>

class Customer
{
public:
	string first_name;
	string last_name;
  string* transactions;
	int account_number;
	int pin_number;
	int balance;
	
	Customer(const string& f,const string& l ,const int a, const int p, int bal)
    : first_name(f), last_name(l), account_number(a), pin_number(p), balance(bal), transactions(new string [10]) {}
};
