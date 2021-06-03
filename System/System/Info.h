#pragma once
#include <string>
using namespace std;

class Info
{
public:
	Info();
	bool change(string);		//Change the password
	bool check(string);			//Check if the password is correct
	string get_Password();

private:
	string password;
	bool safe(string);				//Check if the password is safe enough
};