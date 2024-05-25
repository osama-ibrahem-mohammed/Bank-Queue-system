#pragma once

#include <iostream>
#include<string>
#include<queue>
#include "teller.h"
#include "customer.h"
using namespace std;
class banksystem
{
private:
	int num_teller;        ////////number of tellers
	int total_waiting;       ///////total waiting time
	int total_serviced;      ////////total service time
     int total_customers;       ////total number of customers

public:
	teller* t;
	queue<customer>* q;
	banksystem()
	{
		q = new queue<customer>();
		total_waiting = 0;
		total_serviced = 0;
		total_customers = 0;
	}
	void teller_initialize(int count)
	{
		t = new teller[count];
		num_teller = count;
	}
	void enqueue_customer(int arrival,int serviced)
	{
		//adding new customer
		int flag = 0;
		for (int i = 0;i < 3;i++)
		{
			if (t[i].available)
			{
				if (q->empty())
				{
					customer c;
					c.arrival_time = arrival;
					c.service_time = serviced;
					c.departure_time = arrival + serviced;
					c.waiting_time = 0;
					c.window_num = i;
					q->push(c);
					t[i].available = false;
					t[i].finishsevice_time = c.departure_time;
					flag = 1;

					break;

				}
				else
				{

				}
				
			}
		}

		if (flag = 0)
		{
			int minIndex = 0;
			for (int i = 0;i < num_teller;i++)
			{

				if (t[i].finishsevice_time< t[minIndex].finishsevice_time)
					minIndex = i;
			}

			customer c;
			c.arrival_time = arrival;
			c.service_time = serviced;
			c.departure_time = t[minIndex].finishsevice_time + serviced;
			c.waiting_time = t[minIndex].finishsevice_time - arrival;
			
			q->push(c);

		}
		////end adding
	// 

	}

	
	// dequeue customers
	void dequeue_customer(int arrival)
	{
		if (!q->empty())
		{
			
			for (int i = 0;i < num_teller;i++)
			{
				for (int i = 0; i < num_teller; i++)
				{
					
					if (t[i].available == false && q->front().window_num == i)
					{
						if (q->front().departure_time <= arrival)
						{
							q->pop();
							t[i].available = true;
						}

					}
				}
				
			}
		}
		
	}


};

