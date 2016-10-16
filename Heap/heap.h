#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include <functional>
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#define forn(x) for(int y=1; y<=x; y++)
#define pb push_back
#define h(x) cout<<"\n:"<<x<<":\n";
using namespace std;

template <class T>  class maxHeap
{   public:
    vector<T> arr;
    int left=0, mid=0, right=0;

    public:

    maxHeap();
    maxHeap(vector<T>&);

    void push(const T&);
    void pop();
    T top();
    void print();
    void printArray();
    void getMedian();

    int percolateUp(int);
    void percolateDown(int);
    T getMax();
    void heapify();

    void incrementPriority(int);
    void printMedian();
    void setMedian(int n);
    int justGreaterThan(int n);
    int justLessThan(int n);
};

//MAXHEAP CONSTRUCTORS
template <class T>  maxHeap<T>::maxHeap()
{
    arr.resize(1);
}

template <class T>  maxHeap<T>::maxHeap(vector<T>& vect)
{
    arr = vect;
    heapify();
}


//MAXHEAP I/O
template <class T>  void maxHeap<T>::push(const T& ele)
{
    arr.pb(ele);
    int n = percolateUp(arr.size()-1); cout<<"\nCurr Element is at: "<<n<<" \n";
    setMedian(n);
}

template <class T>  void maxHeap<T>::print()
{
    int i=1, dots=0;

    std::function <void (int,int)> f = [&] (int i, int dots)
    {
        if(i >= arr.size())
        {   return;}
        cout<<endl;
        forn(dots)  cout<<". ";
        cout<<"\\_"<<arr[i];

        f(2*i, dots+1);
        f(2*i+1, dots+1);
    };

    f(i,dots);
}

template <class T>  void maxHeap<T>::printArray()
{
    forn(arr.size()-1)
    {   cout<<y<<"\t";}
    cout<<endl;
    forn(arr.size()-1)
    {   cout<<arr[y]<<"\t";}
}

template <class T>  void maxHeap<T>::getMedian()
{
    if((arr.size()-1)%2 == 0)
    {   cout<<arr[left]<<" ("<<left<<") "<<arr[mid]<<" ("<<mid<<") "<<setw(20)<<"Right-  "<<arr[right]<<" ("<<right<<") ";}
    else
    {   cout<<arr[mid]<<" ("<<mid<<")"<<setw(20)<<"Left & Right-  "<<arr[left]<<" ("<<left<<") "<<"\t "<<arr[right]<<" ("<<right<<") ";}
}

//MAXHEAP HELPERS
template <class T>  void maxHeap<T>::percolateDown(int i)
{
    auto contains = [&] (int k) {   return k < arr.size() ? 1:0;};

    while(contains(2*i))
    {
        int small = 2*i;
        if(contains(2*i+1) && arr[2*i+1] > arr[2*i])
        {   small = 2*i+1;}

        if(arr[i] < arr[small])
        {   swap(arr[i], arr[small]);
            i = small;
        }
        else
        {   break;}
    }
}

template <class T>  void maxHeap<T>::pop()
{
    if(arr.size() == 1)
    {   throw "Heap Empty Exception";}

    T ele = arr.back();
    arr.pop_back();

    if(arr.size() > 1)
    {   arr[1] = ele;
        percolateDown(1);
    }
}

template <class T>  T maxHeap<T>::getMax()
{
    return arr[1];
}

template <class T>  void maxHeap<T>::heapify()
{
    for (int i = arr.size()/2; i >=1; i--)
    {   percolateDown(i);}
}

template <class T>  int maxHeap<T>::percolateUp(int i)
{
    while(i>1)
    {
        if(arr[i] > arr[i/2])
        {   swap(arr[i],arr[i/2]);
            i/=2;
        }
        else
        {   break;}
    }
    return i;
}

//MAXHEAP MISC
template <class T>  void maxHeap<T>::incrementPriority(int i)
{
    arr[i]++;
    percolateUp(i);
}

template <class T>  void maxHeap<T>::setMedian(int n)
{
    if(arr.size() == 2)
    {   mid = 1;}

    //if there were two medians before addition (number of elements after addition is odd)
    if(arr.size()%2==0)
    {   //cout<<"\nhere:"<<arr[n]<<"here:";

        //if element added is less than current medians
        if(arr[n]<=arr[left] && arr[n]<arr[mid])
        {   right = mid;
            mid = left;
            left = justLessThan(mid);
        }
        //if element added lies in between current medians
        else if(arr[n]>arr[left] && arr[n]<arr[mid])
        {   right = mid;
            mid = n;
        }
        //if element added is greater than current medians
        else if(arr[n]>arr[left] && arr[n]>=arr[mid])
        {   if(arr.size() == 4)
            {   right = n;}
        }
    }
    //if there was one median before addition (number of elements after addition is even)
    else
    {
        //if element added is less than current median
        if(arr[n]<=arr[mid])
        {   if(arr.size() == 3)
            {   left = n;}
        }
        //if element added is greater than current median
        else
        {   if(arr.size() == 3)
            {   left = mid;
                mid = n;
            }
            else
            {   left = mid;
                mid = right;
                right = justGreaterThan(mid);
            }
        }
    }
}

template <class T>  int maxHeap<T>::justGreaterThan(int n)
{
    int parent = n/2;
    int sibling = (n%2==0) ? n+1:n-1;

    if(sibling >= arr.size() || arr[sibling] < arr[n])
    {   return parent;}

    queue<int> Q;
    Q.push(sibling);
    int nextMax = 1;

    while(Q.empty() == false)
    {
        if(Q.front() < arr.size() && arr[Q.front()] >= arr[n])
        {
            if(arr[Q.front()] < arr[nextMax])
            {   nextMax = Q.front();}
            Q.push(2*Q.front());
            Q.push(2*Q.front()+1);
        }
        Q.pop();
    }
    return nextMax;
}

template <class T>  int maxHeap<T>::justLessThan(int n)
{
    int sibling = (n%2 == 0) ? n+1:n-1;
    int child = -1;

    if(2*n < arr.size())
    {
        if(2*n+1 < arr.size())
        {   child = (arr[2*n] >= arr[2*n+1]) ? 2*n:2*n+1;}
        else
        {   child = 2*n;}
    }

    if(sibling <= child)
    {   return child;}

    int nextMin = child;
    queue<int> Q;
    Q.push(sibling);

    while(Q.empty() == false)
    {
        int curr = Q.front();
        if(curr < arr.size() && arr[curr] <= arr[n])
        {
            if(arr[curr] > arr[nextMin])
            {   nextMin = curr;}
            Q.push(2*curr);
            Q.push(2*curr+1);
        }
        Q.pop();
    }
    return nextMin;
}



#endif // HEAP_H_INCLUDED
