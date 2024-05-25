#pragma once
#include <iostream>
#include<string>
#include"myqueue.h"
#include"teller4.h"
#include"customer4.h"


class banksystem4
{
public:
	int num_teller;        ////////number of tellers
	int total_waiting;       ///////total waiting time
	int total_serviced;      ////////total service time
	int total_customers;       ////total number of customers
	teller4* t;
	myqueue *q;
	banksystem4()
	{
		q = new myqueue();
		total_waiting = 0;
		total_serviced = 0;
		total_customers = 0;
	}
	void teller_initialize(int count)
	{
		t = new teller4[count];
		num_teller = count;
	}
	void enqueue_customer(int arrival, int serviced,char vip)
	{
		//check the shortest teller queue
		int minIndex = 0;
		for (int i = 0;i < num_teller;i++)
		{

			if (t[i].finishsevice_time < t[minIndex].finishsevice_time)
				minIndex = i;
		}
		customer4 c;
		c.window_num = minIndex;
		c.arrival_time = arrival;
		c.service_time = serviced;
		if (vip == 'y')
			c.vip = true;
		else
			c.vip = false;
		q->push(&c, t[minIndex].finishsevice_time, t[minIndex].present_finish);

		//set total properties for all
		assign_total(serviced, c.waiting_time);
		//set total properties for teller
		assign_teller(minIndex, serviced);
		dequeue_customer();
		
	}
	void assign_total(int serviced_time, int waiting_time)
	{
		// set total properties
		total_serviced += serviced_time;
		total_waiting += waiting_time;
		total_customers++;
	}
	void assign_teller(int min_index,int service_time)
	{	
		t[min_index].totalserv_time += service_time;
		t[min_index].num_customer++;
	}
	//refresh the windows, 
	void availablewindow()
	{

		for (int i = 0;i < num_teller;i++)
		{

			if (t[i].present_finish <= q->front()->arrival_time)
				t[i].available = true;
		}
	}

	// dequeue customers
	void dequeue_customer()      ///you could use arrival time to refresh the queue
	{

		if (!q->isEmpty())
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
					if (t[i].available == true && q->front()->window_num == i)
					{
						t[i].present_finish = q->front()->departure_time;
						t[i].available = false;
						q->pop();						
						flag = 0;
					}
					if (q->isEmpty())
						break;
				}
			}

		}


	}
	////calculate the avg waiting time
	void calcAvgWaiting()
	{
		if (total_customers == 0)
			cout << "there is no customer yet\n";
		else
			cout << "avg waiting time is " << total_waiting / total_customers << endl;
	}
	////calculate the avg service
	void calcAvgservice()
	{

		if (total_customers == 0)
			cout << "there is no customer yet" << endl;
		else
			cout << "avg service time is " << total_serviced / total_customers << endl;
	}
	//utilization of every teller
	void calaUtillization()
	{
		for (int i = 0; i < num_teller; i++)
		{
			if (t[i].num_customer == 0)
				cout << "there is no customer in teller number " << i + 1 << endl;
			else
				cout << "utilization for teller number " << i + 1 << " is " << t[i].totalserv_time / t[i].num_customer << endl;
		}

	}
	//display queue
	void display()
	{
		q->Display();
	}
};

