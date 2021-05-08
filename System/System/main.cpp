#include <iostream>
#include "Info.h"
#include "Flow.h"
#include "MANAGEMENT_SYSTEM.h"
using namespace std;

int main()
{
//test flow
#if 0
	Flow My_Flow;
	Bill b1 = {0, Date(21,4,1), "Father", 3000, 2, 1, "Pocket Money"};
	My_Flow.add(b1);
	Bill b2 = { 1, Date(20,12,1), "Taobao", 100, 4, 1, "Shopping" };
	Bill b3 = { 1, Date(20,12,2), "Taobao", 100, 4, 1, "Shopping" };
	My_Flow.add(b2);
	My_Flow.add(b2);
	system("cls");
	My_Flow.find_month(Date(21, 4, 0));
	system("cls");
	My_Flow.find_tag(1);
#endif

//main program
#if 1
	MANAGEMENT_SYSTEM System;
	System.run();
#endif
	return 0;
}