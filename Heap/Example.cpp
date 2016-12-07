#include "heap.h"
using namespace std;

int main()
{
    vector<int> V={0,1,4,2,3,5,6,8,9,7};
    maxHeap<int> H(V);
    H.print();
}
