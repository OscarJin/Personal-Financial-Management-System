#include "MANAGEMENT_SYSTEM.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;

MANAGEMENT_SYSTEM::MANAGEMENT_SYSTEM()
{
	ifstream history("history.txt", ios::in);
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
		cin >> new_password;
		if (personal_info.change(new_password))
		{
			cout << "Congratulations! You have set up your password!" << endl;
			break;
		}
		cout << "Your password is not safe enough. Please enter a new one." << endl;
	} while (true);
}

void MANAGEMENT_SYSTEM::save()
{
	remove("history.txt");
	ofstream record("history.txt", ios::out);				//cover old history
	record << personal_info.get_Password() << endl;			//write password
	record << personal_flow.get_Size() << endl;				//write num of bills
	personal_flow.save(record);
	record.close();
}

MANAGEMENT_SYSTEM::~MANAGEMENT_SYSTEM()
{
	save();
}

bool MANAGEMENT_SYSTEM::Check_Password()
{
	string password_input;
	do
	{
		cout << "Please enter your password:" << endl;
		cin >> password_input;
		if (personal_info.check(password_input))
			return true;
		else
			cout << "Password Incorrect" << endl;
	} while (true);
}

//main
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
		add_bill();
		break;
	case 5:
		save();
		exit(0);
	default:
		break;
	}
}

inline void MANAGEMENT_SYSTEM::_return()
{
	system("cls");
	run();
}

void MANAGEMENT_SYSTEM::info_manange()
{
	cout << "Please choose:" << endl;
	cout << "1-Change Password" << endl;
	cout << "2-Balance" << endl;
	cout << "3-Return" << endl;
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
			cin >> new_password;
			if (personal_info.change(new_password))
			{
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
		_return();
		break;
	default:
		break;
	}
}

void MANAGEMENT_SYSTEM::add_bill()
{
	cout << "Please choose:" << endl;
	cout << "1-Regular Bookkeeping" << endl;
	cout << "2-Split the bill" << endl;
	cout << "Caution: you may only split the bill of the latest three days!" << endl;
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
		char _source;
		_source = cin.get();
		while ((_source = cin.get()) != '\n')
			new_bill.source.push_back(_source);
		cout << "Please enter the amount: " << endl;
		cin >> new_bill.money;
		cout << "Please choose your payment method (see the user manual for more information):" << endl;
		cout << "0-Credit Card\t1-Debit Card\t2-Wechat Pay\t3-Alipay\t4-Cash" << endl;
		cin >> new_bill.method;
		cout << "Please add a tag: 0-Income 1-Food 2-Daily Necessities 3-Education 4-Entertainment 5-Transportation 6-Other" << endl;
		cin >> new_bill.tag_no;
		cout << "Details(you may write anything!):" << endl;
		char _detail;
		_detail = cin.get();
		while ((_detail = cin.get()) != '\n')
			new_bill.detail.push_back(_detail);
		Check_Password();
		personal_flow.add(new_bill);
		cout << "Success!" << endl;
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
