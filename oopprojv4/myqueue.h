#pragma once
#include<iostream>
#include"Node.h"
#include"customer4.h"
using namespace std;

class myqueue
{
    Node* head, * tail;

public:
    myqueue()
    {
        head = tail = NULL;
    }
    void push(customer4 *c,int &finish_service,int present_finish)
    {
        Node* node = new Node(c);
        int min_place = getPlaceOfNode(c);
       
         
        if (head == NULL)
        {
            head = tail = node; 
            node->c->simple_assign(node->c->arrival_time, node->c->service_time, finish_service);
        }
       
        else
        {          
            if (min_place==-1)
            {
                tail->Next = node;
                tail = node;
                node->c->simple_assign(node->c->arrival_time, node->c->service_time, finish_service);
            }
            else 
            {
                Node* temp = getPointerToNode(min_place);
                if (temp == head)
                {
                    head->prev = node;
                    node->Next = head;
                    head = node;
                    node->c->complicate_assign(node->c->arrival_time, node->c->service_time, finish_service, present_finish);

                }
                temp->prev->Next = node;
                node->prev = temp->prev;
                node->Next = temp;                
                temp->prev = node; 
                int dept = node->prev->c->departure_time;
                node->c->complicate_assign2(node->c->arrival_time, node->c->service_time, finish_service, dept);

            }
        }

    }
    customer4* pop()
    {
        
        customer4 *c2 = head->c;
        Node* temp = head;
        head = head->Next;
        if (head == NULL)
            tail = NULL;
        else
        head->prev = NULL;
        delete temp;
        
        return c2;

    }
    customer4* front()
    {
        return head->c;
    }
    customer4* back()
    {
        return tail->c;
    }
    bool isEmpty()
    {   
            return head == NULL;
    }
    int getPlaceOfNode(customer4* c)
    {
        Node* node = new Node(c);
        Node* temp = tail;
        int minplace = -1;
        int index = 0;
        while (temp!=NULL)
        {
            if ((node->c->vip && !temp->c->vip) || (node->c->arrival_time < temp->c->arrival_time))
            {
                if (node->c->window_num == temp->c->window_num)
                {

                    temp->c->departure_time += node->c->service_time;
                    temp->c->waiting_time += node->c->service_time;
                    minplace = index;
                }
            }
            temp = temp->prev;
            index++;
        }
        return minplace;
    }
    Node* getPointerToNode(int minplace)
    {
        Node* temp = tail;
        for (int i = 0; i < minplace; i++)
        {
            temp = temp->prev;
        }
        return temp;
    }

    void Display()
    {
        Node* current = head;

        while (current != NULL)
        {
            cout << "arrival time " << current->c->arrival_time << endl
                << "departure time " << current->c->departure_time << endl
                << "waiting time " << current->c->waiting_time << endl
                << "service time " << current->c->service_time << endl;
            current = current->Next;
        }
    }
    
};




































//void push(customer4* c, int finish_service, int present_finish)
//{
//    Node* node = new Node(c);
//    Node* temp = tail;
//
//    int flag = 0;
//    int flag2 = 0;
//
//    if (head == NULL)
//    {
//        head = tail = node;
//        ///set departue time
//        if (finish_service < c->arrival_time)
//            node->c->departure_time = node->c->arrival_time + node->c->service_time;
//        else
//            node->c->departure_time = finish_service + node->c->service_time;
//        ///set waiting time
//        node->c->waiting_time = finish_service - node->c->arrival_time;
//        if (node->c->waiting_time <= 0)
//            node->c->waiting_time = 0;
//
//
//    }
//
//    else
//    {
//
//        while (flag != 1 || temp != NULL)
//        {
//            flag = 1;
//            if ((node->c->vip && !temp->c->vip) || node->c->arrival_time < temp->c->arrival_time)
//            {
//                temp->c->departure_time += node->c->service_time;
//                temp->c->waiting_time += node->c->service_time;
//                temp = temp->prev;
//                flag = 0;
//                flag2 = 1;
//            }
//
//        }
//        if (flag2 = 0)
//        {
//            tail->Next = node;
//            tail = node;
//            ///set departue time
//            if (finish_service < c->arrival_time)
//                node->c->departure_time = node->c->arrival_time + node->c->service_time;
//            else
//                node->c->departure_time = finish_service + node->c->service_time;
//            ///set waiting time
//            node->c->waiting_time = finish_service - node->c->arrival_time;
//            if (node->c->waiting_time <= 0)
//                node->c->waiting_time = 0;
//        }
//        else if (temp == NULL)
//        {
//            head->prev = node;
//            node->Next = head;
//            head = node;
//            ///set departue time
//            if (present_finish < c->arrival_time)
//                node->c->departure_time = node->c->arrival_time + node->c->service_time;
//            else
//                node->c->departure_time = present_finish + node->c->service_time;
//            ///set waiting time
//            node->c->waiting_time = present_finish - node->c->arrival_time;
//            if (node->c->waiting_time <= 0)
//                node->c->waiting_time = 0;
//
//        }
//        else
//        {
//            temp->Next->prev = node;
//            node->Next = temp->Next;
//            temp->Next = node;
//            node->prev = temp;
//            if (temp->c->departure_time < c->arrival_time)
//                node->c->departure_time = node->c->arrival_time + node->c->service_time;
//            else
//                node->c->departure_time = temp->c->departure_time + node->c->service_time;
//            ///set waiting time
//            node->c->waiting_time = temp->c->departure_time - c->arrival_time;
//            if (c->waiting_time <= 0)
//                c->waiting_time = 0;
//
//        }
//
//
//    }







//}