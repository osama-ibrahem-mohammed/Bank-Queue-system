#pragma once
class teller3
{
public:
	bool available;
	int finishsevice_time;    ///the time of departure of last customer in the window ( distripute customers on tellers)
	int present_finish;       ////when the present customer will finish his time(to know if customer has finished his service)
	int totalserv_time;        ///// for utilization 
	int num_customer;          ///total number of customers teller served
	teller3() {
		available = true;
		num_customer = 0;
		finishsevice_time = 0;
		present_finish = 0;
		totalserv_time = 0;
	}



};

