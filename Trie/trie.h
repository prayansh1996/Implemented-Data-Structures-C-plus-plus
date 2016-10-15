#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
class trie;

class node
{
    vector<node*> child;
    bool end;
    static int count;
    friend class trie;

public:
    static bool isempty(const node*);
    node(): child(26,NULL), end(false){}
};

class trie
{
    node *root;
    static int words;
    static void prettyprint(const node*,int);
    node* delete_word(node*, const char*);
    static void prefix(node*,string,vector<string>&);
    static void clear_trie(node*);

public:
    ~trie();
    bool isempty()    {   return node::isempty(root)? 1:0;}
    trie()  {   root = new node;}
    void insert_word(const char*);
    void insert_paragraph(char *);
    void delete_word(const char* str)   {   root=delete_word(root, str); if(!root) {root=new node;}}
    void prettyprint() const  {   cout<<"\n"; prettyprint(root, 0);}
    bool ispresent(const char *);
    vector<string> prefix(const char*);
};

int trie::words = 0;

//NODE FUNCTIONS
bool node::isempty(const node* parent)
{
    int i;
    for(i=0; i<26; i++)
    {   if(parent->child.at(i)!=NULL)
        {   break;}
    }
    if(i==26)
    {   return 1;}
    return 0;
}

//TRIE FUNCTIONS
trie::~trie()
{   clear_trie(root);
    root = new node;
}


void trie::clear_trie(node *root)
{
    for(int i=0; i<26; i++)
    {   node *child = root->child.at(i);
        if(child)
        {   clear_trie(child);}
    }
    delete root;
}


void trie::insert_word(const char* str)
{
    node *parent=root;
    while(*str)
    {   node *child = parent->child.at(*str - 'a');
        if(child==NULL)
        {   child = new node;
            parent->child.at(*str - 'a') = child;
        }
        parent = child;
        str++;
    }
    parent->end = 1;
    words++;
}


void trie::insert_paragraph(char *str)
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
        insert_word(s);
        while(*str!=0 && (*str==' ' || *str=='\n' || *str=='.' || *str==','))
        {   str++;}
    }
}


void trie::prettyprint(const node* curr_parent, int depth)
{
    if(curr_parent == NULL)
        return;

    for(int i=0; i<curr_parent->child.size(); i++)
    {   if(curr_parent->child.at(i))
        {
            prettyprint(curr_parent->child.at(i), depth + 1);
            int k = depth;
            while(k--)
            {   cout<<".  ";}
            cout<<"\\_";
            cout<<(char)(i + 'a')<<endl;
        }
    }
}


node* trie::delete_word(node *parent, const char *str)
{
    if(!parent)
    {   return NULL;}

    if(*str==0)
    {   if(parent->end==0)
        {   return parent;}
        else
        {   parent->end=0;}

        if(node::isempty(parent))
        {   delete parent;
            return NULL;
        }
        return parent;
    }

    node *child = delete_word(parent->child.at(*str - 'a'), str+1);
    parent->child.at(*str - 'a') = child;

    if(child==NULL)
    {
        if(node::isempty(parent))
        {   delete parent;
            return NULL;
        }
    }

    return parent;
}


bool trie::ispresent(const char *str)
{
    node *parent=root;
    while(*str)
    {   node *child = parent->child.at(*str - 'a');
        if(child==NULL)
        {   return 0;}
        parent = child;
        str++;
    }
    if(parent->end==0)
    {   return 0;}
    return 1;
}


vector<string> trie::prefix(const char *str)
{
    node *parent=root;
    vector<string> V;
    string s=str;
    while(*str && *str!='\n')
    {   node *child = parent->child.at(*str - 'a');
        if(child==NULL)
        {   vector<string> Vnull(0);
            return Vnull;
        }
        parent = child;
        str++;
    }

    if(*str=='\n')
    {   s.pop_back();}
    prefix(parent, s, V);
    return V;
}

void trie::prefix(node* parent, const string s, vector<string> &V)
{
    for(int i=0; i<26; i++)
    {   node* child = parent->child.at(i);
        string schild = s;
        if(child)
        {   schild+=(i+'a');
            if(child->end==1)
            {   V.push_back(schild);}
            prefix(child, schild, V);
        }
    }
}

#endif // TRIE_H_INCLUDED
