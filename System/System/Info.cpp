#include "Info.h"
#include <iostream>
using namespace std;

Info::Info()
{
	password = "";
}

//Safe: include uppercase and lowercase letter(s), number(s) and special character(s)
bool Info::safe(string s)
{
	bool upper = false;
	bool lower = false;
	bool num = false;
	bool special = false;
	for (int i = 0; i < s.length(); i++)
	{
		if ((s[i] >= 'A') && (s[i] <= 'Z'))
		{
			upper = true;
			continue;
		}
		else if ((s[i] >= 'a') && (s[i] <= 'z'))
		{
			lower = true;
			continue;
		}
		else if ((s[i] >= '0') && (s[i] <= '9'))
		{
			num = true;
			continue;
		}
		else
		{
			special = true;
		}
	}
	if ((upper == true) && (lower == true) && (num == true) && (special == true))
		return true;
	else
		return false;
}

bool Info::change(string s)
{
	if (safe(s))
	{
		password = s;
		return true;
	}
	else
		return false;
}

bool Info::check(string s)
{
	return (password == s);
}

string Info::get_Password()
{
	return password;
}