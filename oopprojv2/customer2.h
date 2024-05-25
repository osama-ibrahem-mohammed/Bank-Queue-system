#pragma once
#include<string>
using namespace std;
class customer2
{
public:

	int arrival_time;
	int service_time;
	int waiting_time;
	int departure_time;
	int window_num;

	customer2() {
		window_num = -1;
	}


};

