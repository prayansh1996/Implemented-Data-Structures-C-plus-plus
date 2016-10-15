#include <iostream>
#include "..\..\headers\stack.h"
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


template <typename T>
void stack<T>::printqueue()
{
    if(top==NULL)
    {   cout<<" ";
        return;
    }

    stack<T> S2;
    node<T> *temp = top;
    while(temp)
    {   S2.push(temp->data);
        temp = temp->prev;
    }
    while(S2.top)
    {   cout<<S2.top->data<<"->";
        S2.top = S2.top->prev;
    }
}


int main()
{
    stack<int>  S;

    for(float i=1; i<20; i++)
    {  S.printqueue(); S.enqueue(0); cout<<endl;}

    for(float i=1; i<20; i++)
    {   S.printqueue(); S.dequeue(); cout<<endl;}
    return 0;
}
