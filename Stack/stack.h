#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include <iostream>
#include<exception>
using namespace std;

class StackEmptyException: public std::exception
{
    public:
    virtual char const * what() const throw()
    {
        return "Stack is Empty!";
    }
};

template <class T>  class node;
template <class T>  class stack;
template <class T>  ostream& operator<<(const ostream &out, const stack<T> &S);

template <class T>
class node
{
    T data;
    node *prev;
    public:
    node(): data(0), prev(NULL){}
    node(const T &d): data(d), prev(NULL){}
    template <class P>  friend ostream& operator<<(ostream &out, const stack<P> &S);
    template <class P>  friend class stack;
};

template <class T>
class stack
{
    node<T> *top;
    public:
    stack(): top(NULL){}
    ~stack();
    void destroy_stack();
    T& gettop();
    const T& gettop() const;
    bool isempty();
    void push(const T &d);
    void pop();
    template <class P>  friend ostream& operator<<(ostream &out, const stack<P> &S);
    void enqueue(const T &d);
    void dequeue();
    void printqueue();
    bool check_braces(const char *str);
    bool check_useless_braces(const char *str);
};


template <class T>
stack<T>::~stack()
{
    node<T> *temp = top;
    while(top)
    {   temp = top->prev;
        delete top;
        top = temp;
    }
}


template <class T>
void stack<T>::destroy_stack()
{
    node<T> *temp = top;
    while(top)
    {   temp = top->prev;
        delete top;
        top = temp;
    }
}


template <class T>
T& stack<T>::gettop()
{   if (top == NULL)
    {   StackEmptyException excp;
        throw excp;
        int k = 0;
        return k;
    }
    return top->data;
}


template <class T>
const T& stack<T>::gettop() const
{   if (top == NULL)
    {   StackEmptyException excp;
        throw excp;
        return 0;
    }
                            //cout<<"CONST!"; void get(const stack<T> &S)   {   cout<<S.gettop();}-> gets constant;
    return top->data;
}


template <class T>
bool stack<T>::isempty()
{   return top==NULL?0:1;}


template <class T>
void stack<T>::push(const T &d)
{
    node<T> *temp = new node<T>(d);
    if(top==NULL)
    {   top = temp;}
    else
    {   temp->prev = top;
        top = temp;
    }
}


template <class T>
void stack<T>::pop()
{   if (top == NULL)
    {   StackEmptyException excp;
        throw excp;
        return;
    }
    top = top->prev;
}


template <class T>
ostream& operator<<(ostream &out, const stack<T> &S)
{
    node<T> *temp = S.top;
    while(temp)
    {   cout<<temp->data<<"->";
        temp = temp->prev;
    }
    return out;
}


template <>
ostream& operator<<(ostream &out, const stack<char> &S)
{
    node<char> *temp = S.top;
    cout<<"\n";
    while(temp)
    {   cout<<temp->data<<"\n";
        temp = temp->prev;
    }cout<<"--";
    return out;
}
#endif // STACK_H_INCLUDED
