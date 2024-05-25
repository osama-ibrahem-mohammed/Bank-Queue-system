#pragma once
#include <cstddef>
#include "customer4.h"



class Node
{
public:
    customer4 *c;
    Node* Next;
    Node* prev;

    Node(customer4 *c1)
    {
       c=c1;
        Next = NULL;
        prev = NULL;
    }


};
