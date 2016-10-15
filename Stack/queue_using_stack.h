#ifndef QUEUE_USING_STACK_H_INCLUDED
#define QUEUE_USING_STACK_H_INCLUDED
#include "stack.h"
#include <iostream>
using namespace std;

template <typename T>
void stack<T>::enqueue(const T &d)
{    push(d);}


template <typename T>
void stack<T>::dequeue()
{
    stack<T> S2;
    while(top)
    {   S2.push(top->data);
        top = top->prev;
    }
    S2.pop();
    destroy_stack();

    while(S2.isempty())
    {   push(S2.top->data);
        S2.top = S2.top->prev;
    }
}

#endif // QUEUE_USING_STACK_H_INCLUDED
