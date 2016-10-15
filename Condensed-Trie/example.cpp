#include <iostream>
#include "trie2.h"

int main()
{
    trie T,D;
    T.insert("romane");
    T.insert("rom");
    T.insert("romulus");
    T.insert("rubens");
    T.insert("romanus");
    T.insert("ruber");
    T.insert("rubicon");
    T.insert("rubicundus");
    T.misc();

    char str[10000]="The exception handler is declared with the catch keyword immediately after the closing brace of the try block.The syntax for catch is similar to a regular function with one parameter.The type of this parameter is very important,since the type of the argument passed by the throw expression is checked against it,and only in the case they match, the exception is caught by that handler$";
    D.paragraph(str);
    D.misc();
    return 0;
}






