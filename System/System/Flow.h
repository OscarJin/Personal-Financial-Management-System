#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Date.h"
using namespace std;

struct Bill
{
	bool io;		//in=0, out= 1
	Date date;		//when you pay/earn (YY/MM/DD)
	string source;	//to whom you pay/who pay you
	double money;	//how much you pay/earn
	int method;		//payment method: 0-Credit Card 1-Debit Card 2-Wechat Pay 3-Alipay 4-Cash
	int tag_no;		
	//number of tag_no: 0-Income 1-Food 2-Daily Necessities 3-Education 4-Entertainment 5-Transportation 6-Other
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

	int get_Size();
	double get_Balance();
	void save(ofstream&);
	inline void display_balance();
	
private:
	static const string Payment_Method[5];
	static const string Tag[7];
	vector <Bill> flow;
	double balance;
	void display(vector<Bill>::iterator);
	//after each new bill/amendment on date, sort by date (before->now)
	void sort_date();
};
