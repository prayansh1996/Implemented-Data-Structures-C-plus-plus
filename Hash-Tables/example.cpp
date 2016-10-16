#include "myhash.h"
#include <stdlib.h>

using namespace std;

int main()
{
    hashtable<int> H;
    int k;
    int t=0;

    for(int i=0; i<100; i++)
    {
        H.insert(i);
        H.insert(i);
    }
    H.printTable();

    for(int i=0; i<1000; i+=3)
    {
        H.insert(i);
        H.insert(i);
    }
    H.printTable();
    cout<<H.contains(62);
    return 0;
}
