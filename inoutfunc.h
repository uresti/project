#include "classes.h" 

// func starts program's info by assigning 
// values stored in files and assigning them to variables (variables.h)
void Bank_info_start(Bank& Main){
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
	acc_numb_get.close();
	
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
