#include "MANAGEMENT_SYSTEM.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
using namespace std;

MANAGEMENT_SYSTEM::MANAGEMENT_SYSTEM()
{
	ifstream history("history.dat", ios::in);
	if (!history)
		init();
	else
	{
		string password;
		history >> password;
		personal_info.change(password);		//read password

		Check_Password();					//check password

		int total_sum = 0;
		history >> total_sum;				//read num of bills
		for (int i = 0; i < total_sum; i++)
		{
			Bill t;
			history >> t.io;
			history >> t.date.yy;	history >> t.date.mm;	history >> t.date.dd;

			char t_source;
			t_source = history.get();
			while ((t_source = history.get()) != '\n')
				t.source.push_back(t_source);

			history >> t.money;
			history >> t.method;
			history >> t.tag_no;

			char t_detail;
			t_detail = history.get();
			while ((t_detail = history.get()) != '\n')
				t.detail.push_back(t_detail);

			personal_flow.add(t);
			system("cls");
		}
		cout << "Initializing finished!" << endl;
		cout << "Welcome to Personal Financial Management System!" << endl;
		history.close();
	}
}

void MANAGEMENT_SYSTEM::init()
{
	cout << "Welcome to Personal Financial Management System!" << endl;
	cout << "For your safety, you are required to set up a password first. The password should include uppercase and lowercase letter(s), number(s) and special character(s)." << endl;
	string new_password;
	do
	{
		cout << "Now please enter your password: " << endl;
		new_password = password_input();
		if (personal_info.change(new_password))
		{
			Check_Password();
			cout << "Congratulations! You have set up your password!" << endl;
			break;
		}
		cout << "Your password is not safe enough. Please enter a new one." << endl;
	} while (true);
}

void MANAGEMENT_SYSTEM::save()
{
	remove("history.dat");
	ofstream record("history.dat", ios::out);				//cover old history
	record << personal_info.get_Password() << endl;			//write password
	record << personal_flow.get_Size() << endl;				//write num of bills
	personal_flow.save(record);
	record.close();
}

MANAGEMENT_SYSTEM::~MANAGEMENT_SYSTEM()
{
	save();
	cout << "GOODBYE!" << endl;
}

bool MANAGEMENT_SYSTEM::Check_Password()
{
	string input = "";
	do
	{
		cout << "Please enter your password:" << endl;
		input = password_input();
		if (personal_info.check(input))
			return true;
		else
			cout << "Password Incorrect!" << endl;
	} while (true);
}

inline void MANAGEMENT_SYSTEM::input_string(string& s)
{
	char new_s;
	new_s = cin.get();
	while ((new_s = cin.get()) != '\n')
		s.push_back(new_s);
}

inline string MANAGEMENT_SYSTEM::password_input()
{
	string input = "";
	while (true) {
		char c = _getch();
		if (c == '\r')
		{
			cout << endl;
			break;
		}
		input.push_back(c);
		cout << "*";
	}
	return input;
}

//main menu
void MANAGEMENT_SYSTEM::run()
{
	cout << "Please choose:" << endl;
	cout << "1-Personal Info" << endl;
	cout << "2-Bookkeeping" << endl;
	cout << "3-Search/Amend" << endl;
	cout << "4-Financial Analysis" << endl;
	cout << "5-Exit" << endl;
	int opt;
	cin >> opt;
	switch (opt)
	{
	case 1:
		system("cls");
		info_manange();
		break;
	case 2:
		system("cls");
		try
		{
			add_bill();
		}
		catch (double money)
		{
			cout << money << " is an invalid input!" << endl;
		}
		catch (int choice)
		{
			cout << choice << " is an invalid input!" << endl;
		}
		break;
	case 3:
		system("cls");
		search_amend();
		break;
	case 4:
		system("cls");
		Analysis();
		break;
	case 5:
		save();
		cout << "GOODBYE!" << endl;
		exit(0);
	default:
		break;
	}
}

//return to main menu
inline void MANAGEMENT_SYSTEM::_return()
{
	system("cls");
	run();
}

//sub menu 1
void MANAGEMENT_SYSTEM::info_manange()
{
	cout << "Please choose:" << endl;
	cout << "1-Change Password" << endl;
	cout << "2-Balance" << endl;
	cout << "3-Print Account" << endl;
	cout << "4-Return" << endl;
	int opt1;
	cin >> opt1;
	string new_password;
	switch (opt1)
	{
	case 1:
		Check_Password();
		do
		{
			cout << "Please enter your new password: " << endl;
			new_password = password_input();
			if (personal_info.change(new_password))
			{
				Check_Password();
				cout << "Congratulations! You have changed your password!" << endl;
				break;
			}
			cout << "Your password is not safe enough. Please enter a new one." << endl;
		} while (true);
		info_manange();
		break;
	case 2:
		Check_Password();
		personal_flow.display_balance();
		info_manange();
		break;
	case 3:
		Check_Password();
		personal_flow.print_all();
		info_manange();
		break;
	case 4:
		_return();
		break;
	default:
		break;
	}
}

//sub menu 2
void MANAGEMENT_SYSTEM::add_bill()
{
	cout << "Please choose:" << endl;
	cout << "1-Regular Bookkeeping" << endl;
	cout << "2-Split the bill" << endl;
	cout << "Caution: you can only split the bill of the latest month!" << endl;
	cout << "3-Return" << endl;
	int opt2;
	cin >> opt2;
	Bill new_bill;
	switch (opt2)
	{
	case 1:
		cout << "You are adding a new bill now..." << endl;
		cout << "Please choose: 0-Income\t1-Payment" << endl;
		cin >> new_bill.io;
		cout << "When you paid the bill? (in the format of \"YY MM DD\")" << endl;
		cin >> new_bill.date.yy >> new_bill.date.mm >> new_bill.date.dd;
		cout << "Where did your money come from/go?" << endl;
		input_string(new_bill.source);
		cout << "Please enter the amount: " << endl;
		cin >> new_bill.money;
		if (new_bill.money <= 0)
			throw new_bill.money;		//money should > 0
		cout << "Please choose your payment method (see the user manual for more information):" << endl;
		cout << "0-Credit Card\t1-Debit Card\t2-Wechat Pay\t3-Alipay\t4-Cash\t5-Student Card" << endl;
		cin >> new_bill.method;
		if (new_bill.method < 0 || new_bill.method > 5)
			throw new_bill.method;		//invalid method input
		cout << "Please add a tag: 0-Income 1-Food 2-Daily Necessities 3-Education 4-Entertainment 5-Transportation 6-Other" << endl;
		cin >> new_bill.tag_no;
		if (new_bill.tag_no < 0 || new_bill.tag_no > 6)
			throw new_bill.tag_no;		//invalid tag input
		cout << "Details(you may write anything!):" << endl;
		input_string(new_bill.detail);
		Check_Password();
		try
		{
			personal_flow.add(new_bill);
			cout << "Success!" << endl;
		}
		catch (double balance)
		{
			cout << "Insufficient Balance!" << endl;
		}
		save();
		add_bill();
		break;

	case 2:
		if (personal_flow.show_latest_month())
		{
			cout << "Please enter the number of bill: " << endl;
			int no;
			cin >> no;
			cout << "Please enter the number of people: " << endl;
			int num;
			cin >> num;
			Check_Password();
			try
			{
				personal_flow.split(no, num);
			}
			catch (int num)
			{
				cout << num << " is an invalid input!" << endl;
			}
		}
		save();
		add_bill();
		break;

	case 3:
		_return();
		break;
	default:
		break;
	}
}

//sub menu 3
void MANAGEMENT_SYSTEM::search_amend()
{
	cout << "Please choose:" << endl;
	cout << "1-Search by date" << endl;
	cout << "2-Search by month" << endl;
	cout << "3-Search by vendors (latest month)" << endl;
	cout << "4-Search by tags (latest month)" << endl;
	cout << "5-Return" << endl;
	int opt3;
	cin >> opt3;
	int y, m, d;
	string s_input = "";
	bool find = false;
	switch (opt3)
	{
	case 1:
		cout << "Please enter the date you want to search (in the format \"YY MM DD\"):" << endl;
		cin >> y >> m >> d;
		Check_Password();
		if (personal_flow.find_date(Date(y, m, d)))
			find = true;
		break;
	case 2:
		cout << "Please enter the month you want to search (in the format \"YY MM\"):" << endl;
		cin >> y >> m;
		Check_Password();
		if (personal_flow.find_month(Date(y, m, 0)))
			find = true;
		break;
	case 3:
		cout << "Pleae enter the vendor you want to search:" << endl;
		input_string(s_input);
		Check_Password();
		if (personal_flow.find_source(s_input))
			find = true;
		break;
	case 4:
		cout << "Please input the tag you want to search:" << endl;
		cout << "0-Income 1-Food 2-Daily Necessities 3-Education 4-Entertainment 5-Transportation 6-Other" << endl;
		cin >> y;
		Check_Password();
		if (personal_flow.find_tag(y))
			find = true;
		break;
	case 5:
		_return();
		break;
	default:
		break;
	}

	if (find)
	{
		cout << "Do you need to make any changes? 0-No\t1-Yes" << endl;
		bool change;
		cin >> change;
		if (change)
		{
			cout << "Please enter the number of bill: " << endl;
			int no;
			cin >> no;
			cout << "1-Change the tag" << endl;
			cout << "2-Change the details" << endl;
			int opt31;
			cin >> opt31;
			int _tag;
			string _detail = "";
			switch (opt31)
			{
			case 1:
				cout << "Please add a new tag: 0-Income 1-Food 2-Daily Necessities 3-Education 4-Entertainment 5-Transportation 6-Other" << endl;
				cin >> _tag;
				Check_Password();
				try
				{
					personal_flow.amend_tag(no, _tag);
				}
				catch (int i)
				{
					cout << "Invalid input!" << endl;
				}
				break;
			case 2:
				cout << "Please rewrite the details:" << endl;
				input_string(_detail);
				Check_Password();
				personal_flow.amend_detail(no, _detail);
				break;
			default:
				break;
			}
		}
	}
	save();
	search_amend();
}

//sub menu 4
void MANAGEMENT_SYSTEM::Analysis()
{
	//config
	cout << "Welcome to Financial Analysis System!" << endl;
	int y, m;
	cout << "Please enter the month you want to analysis (in the format \"YY MM\"):" << endl;
	cin >> y >> m;
	cout << "Total income/expenditure? 0-No\t1-Yes" << endl;
	bool _total;
	cin >> _total;
	cout << "Analyse by tag? 0-No\t1-Yes" << endl;
	bool _tag;
	cin >> _tag;
	cout << "Sort bills of each tag? 0-No\t1-Yes" << endl;
	bool _sort;
	cin >> _sort;
	cout << "Account in detail? 0-No\t1-Yes" << endl;
	bool _all;
	cin >> _all;
	Check_Password();
	personal_flow.analysis(Date(y, m, 0), _total, _tag, _sort, _all);
	
	system("pause");
	_return();
}
