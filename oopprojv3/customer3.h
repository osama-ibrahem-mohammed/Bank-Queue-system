#pragma once
#include<string>
using namespace std;
class customer3
{
public:

	int arrival_time;
	int service_time;
	int waiting_time;
	int departure_time;
	int window_num;
	bool vip;
	customer3() {
		window_num = -1;
	}

	// overload < for priority queue
	bool operator<(const customer3& other) const {
		if (vip != other.vip) {
			
			return vip; 
		}
		else {
			
			return arrival_time < other.arrival_time; 
		}
	}

};

