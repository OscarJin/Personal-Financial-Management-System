#pragma once
#include <fstream>
using namespace std;

class Date
{
public:
	int yy;
	int mm;
	int dd;
	Date();
	Date(int, int, int);
	void display_date();
	void display_date(ofstream&);

	bool operator < (const Date& d);
	bool operator == (const Date& d);
};