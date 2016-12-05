#include <iostream>
#include "..\mynode.h"

using namespace std;

int main()
{
    linkedlists L;
    for(int i=0;i<6;i++) {
        L.insert_end(i);
    }
    for(int i=0;i<7;i++) {
        L.printlist();
        L.delete_end();
    }

    return 0;
}
