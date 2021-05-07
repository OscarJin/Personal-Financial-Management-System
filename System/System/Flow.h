#pragma once
#include <vector>
#include <string>
#include "Date.h"
using namespace std;

struct Bill
{
	bool io;		//in=0, out= 1
	Date date;		//when you pay/earn (YY/MM/DD)
	string source;	//to whom you pay/who pay you
	double money;	//how much you pay/earn
	int method;		//payment method: 1-Credit Card 2-Debit Card 3-Wechat Pay 4-Alipay 5-Cash
	int tag_no;		//number of tag_no (default/defined by user)
	string detail;	//why you pay/earn
};

class Flow
{
public:
	Flow();
	void add(const Bill&);
	int find_date(const Date&);			//find by date
	int find_month(const Date&);		//find by year
	int find_source(const string&);		//find by source (latest month)
	int find_tag(int);					//find by tag
	void amend_tag(int, int);
	void amend_detail(int, const string&);
	
private:
	vector <Bill> flow;
	double balance;
	void display(vector<Bill>::iterator);
	void display_balance();
	//after each new bill/amendment on date, sort by date (before->now)
	void sort_date();
};
