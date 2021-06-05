#pragma once
#include "Info.h"
#include "Flow.h"
using namespace std;

class MANAGEMENT_SYSTEM
{
public:
	MANAGEMENT_SYSTEM();
	~MANAGEMENT_SYSTEM();
	void run();

private:
	Info personal_info;
	Flow personal_flow;
	bool Check_Password();
	inline void input_string(string&);	//include space
	inline string password_input();		//only show *
	void init();
	void save();
	template<class T>
	inline void error(T);			//output input error

	inline void _return();		//return to main menu
	void info_manange();		//menu1
	void add_bill();			//menu2
	void search_amend();		//menu3
	void Analysis();			//menu4
};

