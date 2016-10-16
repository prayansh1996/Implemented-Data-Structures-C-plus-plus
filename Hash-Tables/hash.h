#ifndef MYHASH_H_INCLUDED
#define MYHASH_H_INCLUDED
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
using namespace std;

template <typename T>
class hashtable
{
    vector< list<T> > V;
    int count;
    float avg;
    float increment;

    private:
    void check();           //IF RETURNS 1, EXPAND AND REHASH
    int getNextPrime(const int&);
    bool checkPrime(const int&);
    int getKey(int);
    int getKey(char*);
    void expandAndRehash();

    public:
    hashtable();
    void insert(T);
    void erase(T);
    bool empty() const;
    void clear();
    bool contains(T);
    void printTable();
    void stuff();
};

template <typename T>
void hashtable<T>::stuff()
{   cout<<avg<<" "<<increment<<endl;}

//PUBLIC FUNCTIONS
template <typename T>
bool hashtable<T>::contains(T ele)
{
    int key = getKey(ele);
    typename list<T>::const_iterator it=V[key].begin();
    for(; it!=V[key].end(); it++)
    {   if( *it == ele)
            break;
    }
    if(it != V[key].end())
    {   return 1;}
    return 0;
}



template <typename T>
hashtable<T>::hashtable()
{
    V.resize(17);
    count = 0;
    increment = 1.0/V.size();
    avg = 0;
}


template <typename T>
void hashtable<T>::insert(T ele)
{
    int key = getKey(ele);
    V[key].push_back(ele);
    count++;
    if(V[key].size() >= 5) {
        expandAndRehash();
    }
    avg+=increment;
    check();
}


template <typename T>
void hashtable<T>::erase(T ele)
{
    int key = getKey(ele);
    V[key].remove(ele);
    count--;
    avg-=increment;
}


template <typename T>
void hashtable<T>::printTable()
{
    typename list<T>::const_iterator it;
    cout<<"\n\n";
    for(int i=0; i<V.size(); i++)
    {   it = V[i].begin();
        cout<<i<<": ";
        while(it!=V[i].end())
        {   cout<<*it;
            if(++it!=V[i].end())
                cout<<"->";
        }
        cout<<"\n\n";
    }

    cout<<"________\n\n";
}


//PRIVATE FUNCTIONS
template <typename T>
void hashtable<T>::check()
{   if(avg>=2)
    {   expandAndRehash();}
}


template <typename T>
int hashtable<T>::getNextPrime(const int &ele)
{
    int n = ele/6, k1=0, k2=0;

    while(1)
    {   n++;

        k1 = 6*n - 1;
        if(checkPrime(k1) && k1!=ele)
        {   return k1;}

        k2 = 6*n + 1;
        if(checkPrime(k2))
        {   return k2;}
    }
}


template <typename T>
bool hashtable<T>::checkPrime(const int &ele)
{
    int root = sqrt(ele);
    for(int i=2; i<=root; i++)
    {   if(ele%i==0)
        {   return 0;}
    }
    return 1;
}


template<typename T>
int hashtable<T>::getKey(int ele)
{   return ele*7%V.size();}


template<typename T>
int hashtable<T>::getKey(char *ele)
{   int key = 0;
    for(int i=0; ele[i]; i++)
    {   key = key^ele[i];
        key <<= 2;
    }
    return key%V.size();
}


template<typename T>
void hashtable<T>::expandAndRehash()
{
    int size = getNextPrime(V.size());
    vector< list<T> > temp = V;
    V.clear();
    V.resize(size);
    typename list<T>::const_iterator it;

    for(int i=0; i<temp.size(); i++)
    {   it = temp[i].begin();
        while(it!=temp[i].end())
        {   V[getKey(*it)].push_back(*it);
            it++;
        }
    }
    avg = (float)count/V.size();
    increment = 1.0/V.size();
}



#endif // MYHASH_H_INCLUDED
