
#include <iostream>
#include "banksystem2.h"
using namespace std;

int main()
{
    

    banksystem2 b;
    int arrival, service,num_teller,choice;
    cout << "please enter  teller\n";
    cin >> num_teller;
    b.teller_initialize(num_teller);
    cout << "enter 1 to enter new customer\n";
    cout << "enter 2 to display the queue\n";
    cout << "enter 3 to display the avg of service time\n";
    cout << "enter 4 to display the avg of waiting time\n";
    cout << "enter 5 to display the utillization of teller\n";
    while (true)
    {
        cout << "please enter  choice\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "please enter arrival and serv and teller\n";
            cin >> arrival >> service;
            b.enqueue_customer(arrival, service);
            break;
        case 2:
            b.display_queue();
            break;
        case 3:
            b.calcAvgservice();
            break;
        case 4:
       b.calcAvgWaiting();
       break;
        case 5:
            b.calaUtillization();
            break;
        default:
            cout << "not valid number\n";

        }
           

        
        
    }
    
}

