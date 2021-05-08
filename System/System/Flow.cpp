#include "Flow.h"
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

//NOTE: NO. DISPLAYED IS REAL+1!!!
Flow::Flow()
{
	balance = 0;
}

void Flow::display(vector<Bill>::iterator it)
{
	cout << "NO." << it - flow.begin() + 1 << "\t";
	if(it->io)
		cout << "PAYMENT" << endl;
	else
		cout << "INCOME" << endl;

	cout << "DATE:"; it->date.display_date();

	if (it->io)
		cout << "TO: ";
	else
		cout << "FROM: ";
	cout << it->source << endl;

	cout << "AMOUNT: CNY" << it->money << endl;

	cout << "PAYMENT METHOD: ";
	switch (it->method)
	{
	case 1:
		cout << "CREDIT CARD" << endl;
		break;
	case 2:
		cout << "DEBIT CARD" << endl;
		break;
	case 3:
		cout << "WECHAT PAY" << endl;
		break;
	case 4:
		cout << "ALIPAY" << endl;
		break;
	case 5:
		cout << "CASH" << endl;
		break;
	default:
		break;
	}

	cout << "TAG: " << it->tag_no << endl;
	cout << "DETAILS: " << it->detail << endl;
}

void Flow::display_balance()
{
	cout << "BALANCE: CNY" << balance << endl;
}

void Flow::sort_date()
{
	/*struct
	{
		bool operator()(Bill b1, Bill b2)
		{
			return b1.date < b2.date;
		}
	}date_less;*/
	sort(flow.begin(), flow.end(), [](Bill b1, Bill b2) {return b1.date < b2.date; });
}

void Flow::add(const Bill& b)
{
	flow.push_back(b);
	if (b.io)
		balance -= b.money;
	else
		balance += b.money;
	display(flow.end() - 1);
	display_balance();
	sort_date();
}

int Flow::find_date(const Date& d)
{
	int res = 0;
	
	for (vector<Bill>::iterator it = flow.begin(); it != flow.end(); it++)
	{
		if (it->date == d)
		{
			res++;
			display(it);
		}
	}
	cout << "There are " << res << " result(s)." << endl;
	return res;
}

//d.dd = 0
int Flow::find_month(const Date& d)
{
	int res = 0;
	for (vector<Bill>::iterator it = flow.begin(); it != flow.end(); it++)
	{
		if ((it->date.yy == d.yy) && (it->date.mm == d.mm))
		{
			res++;
			display(it);
		}
	}
	cout << "There are " << res << " result(s)." << endl;
	return res;
}

//latest month
int Flow::find_source(const string& source)
{
	int res = 0;

	//get date now
	struct tm ltm;
	time_t now;
	time(&now);
	localtime_s(&ltm, &now);
	int year_now = ltm.tm_year - 100;	//YY format
	int month_now = 1 + ltm.tm_mon;

	for (vector<Bill>::iterator it = flow.end() - 1; it != flow.begin(); it--)
	{
		if ((month_now == 1) && (it->date < Date(year_now - 1, 12, 1)))
			break;
		if (it->date < Date(year_now, month_now - 1, 1))
			break;
		//judge latest month
		if (it->source == source)
		{
			res++;
			display(it);
		}
	}
	cout << "There are " << res << " result(s)." << endl;
	return res;
}

int Flow::find_tag(int t)
{
	int res = 0;

	//get date now
	struct tm ltm;
	time_t now;
	time(&now);
	localtime_s(&ltm, &now);
	int year_now = ltm.tm_year - 100;	//YY format
	int month_now = 1 + ltm.tm_mon;

	for (vector<Bill>::iterator it = flow.end() - 1; it != flow.begin(); it--)
	{
		if ((month_now == 1) && (it->date < Date(year_now - 1, 12, 1)))
			break;
		if (it->date < Date(year_now, month_now - 1, 1))
			break;
		//judge latest month
		if (it->tag_no == t)
		{
			res++;
			display(it);
		}
	}
	cout << "There are " << res << " result(s)." << endl;
	return res;
}

void Flow::amend_tag(int i, int new_tag)
{
	flow[i - 1].tag_no = new_tag;
}

void Flow::amend_detail(int i, const string& new_detail)
{
	flow[i - 1].detail = new_detail;
}

int Flow::get_Size()
{
	return flow.size();
}

double Flow::get_Balance()
{
	return balance;
}

void Flow::save(ofstream& rec)
{
	for (vector<Bill>::iterator it = flow.begin(); it != flow.end(); it++)
	{
		rec << it->io << endl;
		rec << it->date.yy << " " << it->date.mm << " " << it->date.dd << endl;
		rec << it->source << endl;
		rec << it->money << endl;
		rec << it->method << endl;
		rec << it->tag_no << endl;
		rec << it->detail << endl;
	}
}
