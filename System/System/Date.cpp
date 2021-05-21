#include "Date.h"
#include <iostream>
#include <fstream>
using namespace std;

Date::Date()
{
	yy = mm = dd = 0;
}

Date::Date(int year, int month, int day): yy(year), mm(month), dd(day) { }

void Date::display_date()
{
	cout << yy << "/" << mm << "/" << dd << endl;
}

void Date::display_date(ofstream& out)
{
	out << yy << "/" << mm << "/" << dd << endl;
}

bool Date::operator<(const Date& d)
{
	if (this->yy < d.yy)
		return true;
	else if (this->yy > d.yy)
		return false;
	else
	{
		if (this->mm < d.mm)
			return true;
		else if (this->mm > d.mm)
			return false;
		else
		{
			if (this->dd < d.dd)
				return true;
			else
				return false;
		}
	}
}

bool Date::operator==(const Date& d)
{
	if ((this->yy == d.yy) && (this->mm == d.mm) && (this->dd == d.dd))
		return true;
	else
		return false;
}