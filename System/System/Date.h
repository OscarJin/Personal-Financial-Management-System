#pragma once
class Date
{
public:
	int yy;
	int mm;
	int dd;
	Date();
	Date(int, int, int);
	void display_date();
	bool operator < (const Date& d);
	bool operator == (const Date& d);
};

