#pragma once

#include <iostream>
#include<string>
#include<queue>
#include "teller2.h"
#include "customer2.h"
using namespace std;
class banksystem2
{
//private:
public:
	int num_teller;        ////////number of tellers
	int total_waiting;       ///////total waiting time
	int total_serviced;      ////////total service time
	int total_customers;       ////total number of customers

public:
	teller2* t;
	queue<customer2>* q;
	banksystem2()
	{
		q = new queue<customer2>();
		total_waiting = 0;
		total_serviced = 0;
		total_customers = 0;
	}
	void teller_initialize(int count)
	{
		t = new teller2[count];
		num_teller = count;
	}
	void enqueue_customer(int arrival, int serviced)
	{
		
		//adding new customer		
			int minIndex = 0;
			for (int i = 0;i < num_teller;i++)
			{

				if (t[i].finishsevice_time < t[minIndex].finishsevice_time)
					minIndex = i;
			}

			customer2 c;
			//set customer property
			c.window_num = minIndex;
			c.arrival_time = arrival;
			c.service_time = serviced;
			///set departue time
			if (t[minIndex].finishsevice_time < arrival)
				c.departure_time = arrival + serviced;
			else
				c.departure_time = t[minIndex].finishsevice_time + serviced;
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
			q->push(c);
			
		////end adding
	// 
			dequeue_customer();
	}


	// dequeue customers
	void dequeue_customer()      ///you could use arrival time to refresh the queue
	{
		
		

		if (!q->empty())
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
					if (t[i].available == true && q->front().window_num == i)
					{
						t[i].present_finish = q->front().departure_time;
						t[i].available = false;
						q->pop();
						if (q->empty())
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
			
			if (t[i].present_finish <= q->front().arrival_time)
				t[i].available = true;
		}
	}
	////calculate the avg waiting time
	void calcAvgWaiting()
	{
		if (total_customers == 0)
			cout<< "there is no customer yet\n";
		else
		cout<< "avg waiting time is " << total_waiting / total_customers<<endl;
	}
	////calculate the avg service
	void calcAvgservice()
	{
		
		if (total_customers == 0)
			cout<< "there is no customer yet"<<endl;
		else
		cout<< "avg service time is " << total_serviced / total_customers<<endl;
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

	/////display the queue
	void display_queue()
	{
		queue<customer2> *temp = q;
		int index = 0;
		while (!temp->empty())
		{
			cout << "customer num " << ++index << endl
				<< "window num " << temp->front().window_num + 1 << endl
				<< "arrival time " << temp->front().arrival_time << endl
				<< "departure time " << temp->front().departure_time << endl
				<< "waiting time " << temp->front().waiting_time << endl
				<< "service time" << temp->front().service_time << endl;
			cout << "--------------------------------------" << endl;
			temp->pop();
		}
	}

};

