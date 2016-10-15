#include <iostream>
#include "trie.h"
#include <vector>

using namespace std;
int main()
{
    char str[10000]="The exception handler is declared hand handyman hanchand hanchandler habitsch";
    trie D;
    D.insert_paragraph(str);
    D.prettyprint();
    vector<string> V=D.prefix("ab");
    for(int i=0; i<V.size(); i++)
    {   cout<<V[i]<<endl;}
    return 0;
}
/*
To take user input->
cin.getline(str, 1000, '$');
*/
