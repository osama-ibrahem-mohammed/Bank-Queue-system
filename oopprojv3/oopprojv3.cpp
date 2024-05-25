
#include <iostream>
#include "banksystem3.h"
using namespace std;

int main()
{
    banksystem3 b;
    int x, y, z;
    char a;
   /* cout << "please enter  teller\n";
    cin >> z;*/
    b.teller_initialize(3);
    while (true)
    {

       /* cout << "please enter arrival and serv and teller\n";
        cin >> x >> y;
        cout << "please enter vip\n";
        cin >> a;*/

        b.enqueue_customer(12, 13,'t');
        b.display_queue();


    }

}

