#define from(x,y,i) for(int i=x; i<y; i++)
#include <iostream>
#include "queue.h"
using namespace std;

int main()
{
    queue<int> Q;
    from(0,6,i) {
        Q.enqueue(i);
    }
    from(0,6,i) {
        cout<<Q;
        Q.dequeue();
    }

    return 0;
}
