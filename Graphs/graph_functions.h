#ifndef GRAPH_FUNCTIONS_H_INCLUDED
#define GRAPH_FUNCTIONS_H_INCLUDED
#include "graph.h"

//WEIGHTED_DIRECTED
//{
template <typename T>
void weighted_directed<T>::addEle(int start, int end, T weight)
{
    typename lp<T>::iterator it = V[start].begin();

    while(it != V[start].end() && it->first < end)
    {   it++;}

    if(it->first == end)
    {   it->second = weight;}                           //WHY DOESNT ERASE WORK
    else
    {   V[start].insert(it,mp(end,weight));}
}

template <typename T>
void weighted_directed<T>::delEle(int start, int end)
{
    typename lp<T>::iterator it = find(V[start],end);
    if(it == V[start].end())
    {   cout<<"\nElement Not Found";}
    else
    {   V[start].erase(it);}
}

template <typename T>
typename lp<T>::iterator weighted_directed<T>::find(lp<T> &L, int end)
{
    typename lp<T>::iterator it = L.begin();
    for(; it!= L.end(); ++it)
    {   if(it->first == end)
        {   return it;}
    }
    return L.end();
}

template <typename T>
void weighted_directed<T>::printBFS()
{
    cout<<endl;
    for(int i=0; i<V.size(); i++)
    {   typename lp<T>::iterator it = V[i].begin();
        while(it != V[i].end())
        {   cout<<i<<" -> "<<it->first<<" with weight = "<<it->second<<endl;
            it++;
        }
    }
}

template <typename T>
void weighted_directed<T>::printNoWeight()
{
    cout<<endl;
    for(int i=0; i<V.size(); i++)
    {   typename lp<T>::iterator it = V[i].begin();
        cout<<i<<" -> ";
        while(it != V[i].end())
        {   cout<<it->first<<" ";
            it++;
        }
        cout<<endl;
    }
}

template <typename T>
ostream& operator<<(ostream& obj, weighted_directed<T> &G)
{
    G.printBFS();
    return obj;
}

template <typename T>
T weighted_directed<T>::getWeight(int start, int end)
{
    return find(V[start], end)->second;
}

//}

//UNWEIGHTED
//{
template <typename T>
void unweighted<T>::addEle(int start, int end)
{   weighted_directed<T>::addEle(start,end,0);}

template <typename P>
ostream& operator<<(ostream& obj, unweighted<P> &G)
{
    G.printNoWeight();
    return obj;
}
//}

//UNDIRECTED
//{
template <typename T>
void undirected<T>::addEle(int start, int end, T weight)
{
    weighted_directed<T>::addEle(start, end, weight);
    weighted_directed<T>::addEle(end, start, weight);
}

template <typename T>
void undirected<T>::delEle(int start, int end)
{
    weighted_directed<T>::delEle(start, end);
    weighted_directed<T>::delEle(end, start);
}

template <typename P>
ostream& operator<<(ostream& obj, undirected<P> &G)
{
    G.printBFS();
    return obj;
}
//}

//UNWEIGHTED_UNDIRECTED
//{
template <typename T>
void unweighted_undirected<T>::addEle(int start, int end)
{
    weighted_directed<T>::addEle(start, end, 0);
    weighted_directed<T>::addEle(end, start, 0);
}

template <typename P>
ostream& operator<<(ostream& obj, unweighted_undirected<P> &G)
{
    G.printNoWeight();
    return obj;
}
//}
#endif // GRAPH_FUNCTIONS_H_INCLUDED
