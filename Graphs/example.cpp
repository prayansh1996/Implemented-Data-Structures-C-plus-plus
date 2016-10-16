#include "graph_functions.h"
#include <stdlib.h>

using namespace std;

int main()
{
    undirected<int> G;
    G.addEle(0,1,3);
    G.addEle(1,2,3);
    G.addEle(2,3,4);
    G.printBFS();
}
