#pragma once

#include <iostream>
#include<string>
#include<queue>
#include "teller3.h"
#include "customer3.h"
using namespace std;
class banksystem3
{
	//private:
public:
	int num_teller;        ////////number of tellers
	int total_waiting;       ///////total waiting time
	int total_serviced;      ////////total service time
	int total_customers;       ////total number of customers

public:
	teller3* t;
	priority_queue<customer3> q;
	banksystem3()
	{
		
		total_waiting = 0;
		total_serviced = 0;
		total_customers = 0;
	}
	void teller_initialize(int count)
	{
		t = new teller3[count];
		num_teller = count;
	}
	void enqueue_customer(int arrival, int serviced,char vip)
	{

		//adding new customer		
		int minIndex = 0;
		for (int i = 0;i < num_teller;i++)
		{

			if (t[i].finishsevice_time < t[minIndex].finishsevice_time)
				minIndex = i;
		}

		customer3 c;

		//set customer property
		c.window_num = minIndex;
		if (vip == 'y')
		{
			c.vip = true;
			if (arrival > t[minIndex].present_finish)
				c.arrival_time = t[minIndex].present_finish;
		}

		else
		{
			c.vip = false;
			c.arrival_time = arrival;
		}
	
		c.service_time = serviced;
		
			
		///set departue time
		if (c.vip)
		{
			c.departure_time = c.arrival_time + serviced;
		}
		else
		{
			if (t[minIndex].finishsevice_time < arrival)
				c.departure_time = arrival + serviced;
			else
				c.departure_time = t[minIndex].finishsevice_time + serviced;
		}

		
		///set waiting time
		c.waiting_time = t[minIndex].finishsevice_time - arrival;
		if (c.waiting_time <= 0)
			c.waiting_time = 0;
		//end customer property
		//set total properties
		total_serviced += serviced;
		total_waiting += c.waiting_time;
		total_customers++;
		//set teller properties			
		t[minIndex].finishsevice_time = c.departure_time;
		t[minIndex].totalserv_time += serviced;
		t[minIndex].num_customer++;

		//push customer
		q.push(c);

		////end adding
	// 
		dequeue_customer();
	}


	// dequeue customers
	void dequeue_customer()      ///you could use arrival time to refresh the queue
	{
		

		if (!q.empty())
		{
			//first make sure to available windows
			availablewindow();
			//dequeue customer from queue 
			int flag = 0;
			while (flag != 1)
			{
				for (int i = 0;i < num_teller;i++)
				{
					// dequeue the ready customer from the queue
					flag = 1;
					if (t[i].available == true && q.top().window_num == i)
					{
						t[i].present_finish = q.top().departure_time;
						t[i].available = false;
						q.pop();
						if (q.empty())
							break;
						flag = 0;
					}

				}
			}

		}


	}
	//refresh the windows, 
	void availablewindow()
	{

		for (int i = 0;i < num_teller;i++)
		{
			int x = t[i].present_finish;
			int y = q.top().arrival_time;
			int z = q.top().window_num;
			if (t[i].present_finish <= q.top().arrival_time)
				t[i].available = true;
		}
	}
	/////display the queue
	void display_queue()
	{
		priority_queue<customer3> temp = q;
		int index = 0;
		while (!temp.empty())
		{
			cout << "customer num " << ++index << endl
				<< "window num " << temp.top().window_num + 1 << endl
				<< "arrival time " << temp.top().arrival_time<<endl
				<< "departure time " << temp.top().departure_time<<endl
				<< "waiting time " << temp.top().waiting_time<<endl
				<< "service time" << temp.top().service_time << endl;
			cout << "--------------------------------------" << endl;
			temp.pop();
		}
	}
	////calculate the avg waiting time
	string calcAvgWaiting()
	{

		if (total_customers == 0)
			return "there is no customer yet";
		else
		return "avg waiting time is " + total_waiting / total_customers;
	}
	////calculate the avg service
	string calcAvgservice()
	{
		if (total_customers == 0)
			return "there is no customer yet";
		else	
		return "avg service time is " + total_serviced / total_customers;
	}
	//utilization of every teller
	string calaUtillization()
	{
		for (int i = 0; i < num_teller; i++)
		{
			if (total_customers == 0)
				cout<< "there is no customer in teller number "<< i + 1<<endl;
			else
			cout << "utilization for teller number " << i + 1 << " is " << t[i].totalserv_time / t[i].num_customer<<endl;
		}

	}

};

