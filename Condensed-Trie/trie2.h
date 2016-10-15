#ifndef TRIE2_H_INCLUDED
#define TRIE2_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>
#define h(x) cout<<x<<'\n';
using namespace std;

class node
{
    string str;
    vector<node*> V;
    bool endbit;
    int numberOfChildren();

    public:
    node();
    node(string arr, bool bit);
    friend class trie;
};

//NODE FUNCTIONS
node::node()
{
    V.resize(26);
}

node::node(string arr, bool bit=0)
{
    str = arr;
    V.resize(26);
    endbit = bit;
}

int node::numberOfChildren()
{
    int num=0;
    for(int i=0; i<26; i++)
    {   if(V[i] != NULL)
        {   num++;}
    }
    return num;
}

class trie
{
    node* root = new node();
    static void misc(node* root, int);

    public:
    long int wordcount;
    void insert(string);
    void remove(string);
    bool contains(string);

    void paragraph(char*);
    void misc() {   misc(root,0);}
    string checkString(string);
};

//TRIE FUNCTIONS
void trie::insert(string s)
{
    s = checkString(s);
    if(s[0] == '\0')
    {   cout<<"\nIncorrect Input\n";
        return;
    }
    string::iterator str = s.begin();   int i=0;

    if(root->V[*str-'a'] == NULL)
    {   node* temp = new node(s,1);
        root->V[*str-'a'] = temp;
        return;
    }

    node* curr = root;
    while(true)
    {
        int k=0;
        string::iterator ch = curr->str.begin();

        while(*ch && *str && *ch == *str)
        {   ch++, i++, k++, str++;}

        if(*str == NULL)                    //IF INPUT STRING FINISHES
        {
            if(*ch == NULL)                 //IF BOTH FINISH
            {   curr->endbit = 1;
                return;
            }
            char c = *ch;   cout<<s<<" "<<c<<endl;

            node* temp = new node(*curr);
            temp->str.erase(0,k);                           //REMOVE FIRST i LETTERS STARTING FROM 0: OLUS

            curr->str.erase(k,100);                         //REMOVE LETTERS FROM *ch TO END: ROM
            for(int k=0; k<26; k++) curr->V[k]=0;
            curr->V[c-'a'] = temp;
            curr->endbit=1;

            wordcount++;
            break;
        }
        else if(*ch == NULL)                //IF NODE FINISHES
        {
            if(curr->V[*str-'a'] == NULL)
            {   node* temp = new node(s.substr(i,100),1);
                curr->V[*str-'a'] = temp;
                wordcount++;
                break;
            }
            else
            {   curr = curr->V[*str-'a'];}
        }
        else                                //IF STRINGS DIFFERENTIATES
        {
            char c = *ch;

            node* temp = new node(*curr);
            temp->str.erase(0,k);                           //REMOVE FIRST i LETTERS STARTING FROM 0: OLUS

            curr->str.erase(k,100);                         //REMOVE LETTERS FROM *ch TO END: ROM
            for(int k=0; k<26; k++) curr->V[k]=0;
            curr->V[c-'a'] = temp;
            curr->endbit=0;

            node* temp2 = new node(s.substr(i,100),1);      //CREATE SUBSTRING OF THE LAST HALF
            curr->V[*str-'a'] = temp2;
            wordcount++;
            break;
        }
    }
}

void trie::remove(string s)
{
    if(!contains(s))
    {   cout<<"\nNode not found\n";
        return;
    }

    node* parent = root;
    string::iterator str = s.begin();
    node* curr = root;

    char currChar=0;
    while(*str)
    {
        parent = curr;
        curr = curr->V[*str-'a'];
        currChar = *str;
        string::iterator ch = curr->str.begin();

        while(*ch && *str && *ch==*str)
        {   ch++, str++;}
    }

    //if node Curr is a leaf node
    if(curr->numberOfChildren() == 0)
    {
        //if parent has exactly two children and parent itself is NOT a word: Merge parent with the other child
        if(parent->numberOfChildren() == 2 && parent->endbit == 0)
        {
            parent->V[currChar-'a'] = NULL;
            delete curr;

            for(int i=0; i<26; i++)
            {   if(parent->V[i] != NULL)
                {   curr = parent->V[i];
                    break;
                }
            }
            parent->str += curr->str;
            parent->V = curr->V;
            parent->endbit = curr->endbit;
            delete curr;
        }
        else
        {
            delete curr;
            parent->V[currChar-'a'] = NULL;
        }
    }
    //if curr is not a leaf node
    else
    {
        //if curr has only one child
        if(curr->numberOfChildren() == 1)
        {
            parent = curr;
            for(int i=0; i<26; i++)
            {   if(curr->V[i] != NULL)
                {   curr = curr->V[i];
                    break;
                }
            }

            parent->str += curr->str;
            parent->V = curr->V;
            parent->endbit = curr->endbit;
            delete curr;
        }
        else
        {   curr->endbit = 0;}
    }
}

bool trie::contains(string s)
{
    node* temp = root;
    string::iterator str = s.begin();

    if(temp->V[*str-'a'] == NULL)
    {   return 0;}
    temp = temp->V[*str-'a'];

    while(true)
    {
        string::iterator ch = temp->str.begin();
        while(*ch && *str && *ch==*str)
        {   ch++, str++;}

        if(!*str)
        {
            if(!*ch)
            {   return temp->endbit;}
            return 0;
        }
        else
        {
            if(temp->V[*str-'a'] == NULL)
            {   return 0;}
            temp = temp->V[*str-'a'];
        }
    }
}

void trie::misc(node* root, int i)
{
    int l=0;

    if(i)
    {
        for(l; l<i; l++) cout<<". ";    cout<<"\\_";
        cout<<root->str;
        if(root->endbit)    {   cout<<";";}
        cout<<endl;
    }
    for(int k=0; k<26; k++)
    {   if(root->V[k] != NULL)
        {   misc(root->V[k],i+1);}
    }
}

void trie::paragraph(char *str)
{
    for(int i=0; str[i]; i++)
    {   str[i]=tolower(str[i]);}
    char s[100];
    while(*str)
    {   int i=0;
        while(*str!=0 && (*str!=' ' && *str!='\n' && *str!='.' && *str!=','))
        {   s[i++]=*str;
            str++;
        }
        s[i]='\0';
        insert(s);
        while(*str!=0 && (*str==' ' || *str=='\n' || *str=='.' || *str==','))
        {   str++;}
    }
}

string trie::checkString(string s)
{
    for(int i=0; i<s.length(); i++)
    {
        if(!isalpha(s[i]))
        {   s[0] = '\0';
            return s;
        }
        if(s[i] >= 'A' && s[i] <='Z')
        {   s[i] += ('a'-'A');}
    }
    return s;
}

#endif // TRIE2_H_INCLUDED
