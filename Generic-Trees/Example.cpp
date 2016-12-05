#define from(x,y,i) for(int i=x; i<y; i++)
#include <iostream>
#include "tree.h"
using namespace std;

int main()
{
    tree<int> T;
    T.maketree(2);
    T.pretty_print();
    cout<<"\nPost Order: ";
    T.print_postorder();

    cout<<"\n\nPre Order: ";
    T.print_preorder(); cout<<"\n\n";
    return 0;
}
