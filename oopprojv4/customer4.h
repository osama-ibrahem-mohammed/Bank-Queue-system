#pragma once
class customer4
{
public:
	int arrival_time;
	int service_time;
	int waiting_time;
	int departure_time;
	int window_num;
	bool vip;

	void simple_assign(int arrival_time,int service_time,int &finish_service)
	{
		///set departue time
		if (finish_service < arrival_time)
		departure_time = arrival_time +service_time;
		else
			departure_time = finish_service + service_time;
		///set waiting time
		waiting_time = finish_service - arrival_time;
		if (waiting_time <= 0)
			waiting_time = 0;

		finish_service = departure_time;
	}
	void complicate_assign(int arrival_time, int service_time, int& finish_service, int present_finish)
	{
		if (present_finish < arrival_time)
			departure_time = arrival_time + service_time;
		else
			departure_time = present_finish + service_time;
		///set waiting time
		waiting_time = present_finish - arrival_time;
		if (waiting_time <= 0)
			waiting_time = 0;

		finish_service += service_time;
	}
	void complicate_assign2(int arrival_time, int service_time, int &finish_service,int dept)
	{
		if (dept < arrival_time)
			departure_time = arrival_time + service_time;
		else
			departure_time = dept + service_time;
		///set waiting time
		waiting_time = dept - arrival_time;
		if (waiting_time <= 0)
			waiting_time = 0;

		finish_service += service_time;
	}
	

};

