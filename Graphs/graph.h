#include <iostream>
#include <vector>
#include <list>
#define mp make_pair
#define pb push_back
using namespace std;

template <class P>   using lp = list< pair<int,P> >;
template <class T>   using vlp = vector< list< pair<int,T> > >;


template <typename T>
class weighted_directed
{
    vlp<T> V;

    protected:
    typename lp<T>::iterator find(lp<T> &L, int end);
    template <typename P>   friend ostream& operator<<(ostream&, weighted_directed<P> &G);

    public:
    weighted_directed(): V(100) {};
    void addEle(int start, int end, T weight);
    void delEle(int start, int end);
    void printBFS();
    void printNoWeight();
    T getWeight(int start, int end);
};


template <typename T>
class unweighted: virtual public weighted_directed<T>
{
    template <typename P>   friend ostream& operator<<(ostream&, unweighted<P> &G);

    public:
    void addEle(int start, int end);
};


template <typename T>
class undirected: virtual public weighted_directed<T>
{
    template <typename P>   friend ostream& operator<<(ostream&, undirected<P> &G);

    public:
    void addEle(int start, int end, T weight);
    void delEle(int start, int end);
    T getWeight(int start, int end);
};


template <typename T>
class unweighted_undirected: public unweighted<T>, public undirected<T>
{
    template <typename P>   friend ostream& operator<<(ostream&, undirected<P> &G);

    public:
    void addEle(int start, int end);//
};
