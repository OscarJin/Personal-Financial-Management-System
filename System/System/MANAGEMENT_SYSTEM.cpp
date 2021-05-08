#include "MANAGEMENT_SYSTEM.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
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

MANAGEMENT_SYSTEM::~MANAGEMENT_SYSTEM()
{
	remove("history.txt");
	ofstream record("history.txt", ios::out);				//cover old history
	record << personal_info.get_Password() << endl;			//write password
	record << personal_flow.get_Size() << endl;				//write num of bills
	personal_flow.save(record);
	record.close();
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
