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
	void init();
	void save();

	inline void _return();
	void info_manange();
	void add_bill();
};

