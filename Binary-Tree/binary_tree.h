#ifndef BT_test_binary_tree_h
#define BT_test_binary_tree_h
#define lz left
#define rz right
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_set>
#include "misc.h"
#include <cmath>


using namespace std;
template <typename T>
class binarytree;


template <typename T>
class node
{
public:
    T data;
    node *left;
    node *right;

public:
    template <typename temp>   friend class binarytree;
    template <typename V> friend void swap(const node<V>* &left, const node<V>* &asright);
    node(): left(NULL), right(NULL), data(0){}
    node(const T &d):   left(NULL), right(NULL), data(d){}
};


template <typename T>
class binarytree
{
public:
    node<T> *root;

    //CREATE TREE
    static node<T>* create_tree_rec(node<T>*);
    void makecompletetree(node<T>*,T,T);
    static node<T>* in_and_post_order(node<T>*, const char *, const char *, const char *, const char *);
    //PRINT TREE
    static void order(const node<T>*, const char*);
    static int getd(node<T>*);
    static int getlrd(node<T>*, char, char);
    //OTHERS
    static node<T>* delete_half_nodes(node<T>*);
    static node<T>* remove_leaf(node<T>*);
    static bool checkequal(const node<T>*, const node<T>*);
    static int isbalanced(node<T>*);
    static void sibling(const node<T>*);
    static bool root_to_leaf(const node<T> *, int, const int &);
    static void mirror(node<T> *);
    static pair< T,vector<T> > max_root_to_leaf(node<T> *parent);
    static int same_level(const node<T> * const);
    static bool check_sum(node<T>*, unordered_set<T>&, const int&);

public:
    binarytree(): root(NULL){}
    ~binarytree();
    //CREATE TREE
    void create_tree_it();
    void maketree();
    void makelargetree();
    void makecompletetree(T a, T b) {   root = new node<T>(1); makecompletetree(root, a, b);}
    void in_and_post_order(const char *in, const char *post) {  root = in_and_post_order(root, in, in+strlen(in)-1, post, post+strlen(post)-1);}
    //PRINT
    void prettyprint();
    void prettyprintnew();
    void order(const char *str)  {   order(root, str);}
    void iterative_inorder();
    void iterative_postorder();
    //OTHERS
    int diameter(T);
    int diameter(node<T>*, T);
    void delete_half_nodes()    {   root=delete_half_nodes(root);}
    int getld(node<T>* parent)  {   return getlrd(parent, 'n', 'l');}
    int getrd(node<T>* parent)  {   return getlrd(parent, 'n', 'r');}
    void remove_leaf()  {   root=remove_leaf(root);}
    bool operator==(const binarytree<T> &B) {   return checkequal(root, B.root);}
    bool isbalanced()   {   return isbalanced(root)==-5? 0: 1; }
    void sibling()  {   sibling(root);}
    bool root_to_leaf(const int &num)   {   int sum = 0;   return root_to_leaf(root, sum, num);}
    void mirror()   {  mirror(root);}
    vector<T> max_root_to_leaf();
    bool same_level()   {   return same_level(root)==-1 ? 0:1;}
    bool check_sum(const int &);
};



//TREE FUNCTIONS
template <typename T>
binarytree<T>::~binarytree()
{
    queue<node<T>*> Q;
    if(!root)
        return;

    Q.push(root);
    while(Q.empty()==false)
    {
        if(Q.front()->left) Q.push(Q.front()->left); //WHAT IF NULL IS PUSHED?
        if(Q.front()->right) Q.push(Q.front()->right);
        delete Q.front();
        Q.pop();
    }

    root = NULL;
}


template <typename T>
void binarytree<T>::create_tree_it()
{
    T data;
    cout<<"Press 0 to end\nEnter Root: ";
    cin>>data;
    root = new node<T>(data);      //CHECK

    queue<node<T>*> Q;
    Q.push(root);

    while(Q.empty()==false)
    {
        node<T> *parent = Q.front();

        cout<<"Enter Left child of "<<parent->data<<": ";
        cin>>data;
        if(data)
        {
            node<T> *left = new node<T>(data);
            parent->left = left;
            Q.push(left);
        }

        cout<<"Enter Right child of "<<parent->data<<": ";
        cin>>data;

        if(data)
        {
            node<T> *right = new node<T>(data);
            parent->right = right;
            Q.push(right);
        }

        Q.pop();
    }
}


template <typename T>
void binarytree<T>::order(const node<T> *root, const char *str)
{
    if(!root)
        return;

    if(!strcmp(str, "preorder"))   cout<<root->data<<' ';
    order(root->left, str);
    if(!strcmp(str, "inorder"))    cout<<root->data<<' ';
    order(root->right, str);
    if(!strcmp(str, "postorder"))  cout<<root->data<<' ';
}


template <typename T>
void binarytree<T>::maketree()
{
    root = new node<T>(10);

    root->left = new node<T>(7);
    root->left->left = new node<T>(5);
    root->left->left->right = new node<T>(6);

    root->right = new node<T>(13);
    root->right->left = new node<T>(11);
    root->right->left->right = new node<T>(12);
    root->right->right = new node<T>(16);
    root->right->right->left = new node<T>(15);
    root->right->right->right = new node<T>(18);
}


template <>
void binarytree<char>::maketree()
{
    char ch='A';
    root = new node<char>(ch++);

    root->left = new node<char>(ch++);
    root->left->left = new node<char>(ch++);
    root->left->left->right = new node<char>(ch++);

    root->right = new node<char>(ch++);
    root->right->left = new node<char>(ch++);
    root->right->left->right = new node<char>(ch++);
    root->right->right = new node<char>(ch++);
    root->right->right->left = new node<char>(ch++);
    root->right->right->right = new node<char>(ch++);
}


template <typename T>
void binarytree<T>::makelargetree()
{
    root = new node<T>(28);

    root->left = new node<T>(7);
    node<T> *l = root->left;


    root->right = new node<T>(46);
    node<T> *r = root->right;


    l->lz = new node<T>(4);
        l->lz->rz =new node<T>(1);
    l->rz = new node<T>(13);
        l->rz->lz = new node<T>(10);
        l->rz->rz = new node<T>(25);
            l->rz->rz->lz = new node<T>(19);
                l->rz->rz->lz->lz = new node<T>(16);
                l->rz->rz->lz->rz = new node<T>(22);

    r->lz = new node<T>(34);
        r->lz->lz = new node<T>(31);
        r->lz->rz = new node<T>(40);
            r->lz->rz->lz = new node<T>(37);
            r->lz->rz->rz = new node<T>(43);
    r->rz = new node<T>(49);
        r->rz->rz = new node<T>(55);
        r->rz->rz->lz = new node<T>(52);
}


template <typename T>
void binarytree<T>::makecompletetree(node<T> *parent, T a, T b)
{
    if(a>b)
        return;

    node<T> *left = new node<T>(a); parent->left = left;
    node<T> *right = new node<T>(a+1); parent->right = right;
    makecompletetree(parent->left, a+2, b);
    makecompletetree(parent->right, a+3, b);
}


template <typename T>
int binarytree<T>::getd(node<T> *parent)
{
    if(parent == NULL)
        return 0;

    int l = getd(parent->left) + 1;
    int r = getd(parent->right) + 1;
    return max(l,r);
}


template <typename T>
int binarytree<T>::getlrd(node<T> *parent, char ch, char input)
{
    if(parent == NULL)
        return 0;

    int add=0;
    if(ch==input)
        add=1;

    return getlrd(parent->left, 'l', input) + getlrd(parent->right, 'r', input) + add;
}


template <typename T>
void binarytree<T>::prettyprintnew()
{
    int k=pow(2, getd(root)), ld=0, rd=0, sub = 0;      if(getd(root)>5) k-=20;
    int x, y=gety() + 1;
    float ratio = 0.8 + (float)getd(root)/10;
    queue< pair<node<T>*, int> > Q;
    queue<int> Q2;

    pair<node<T>*,int> Proot(root, k);
    pair<node<T>*,int> PNULL(NULL, 0);      //CHECK if without 0

    Q.push(Proot);
    Q.push(PNULL);

    while(Q.empty()==false)
    {
    static int i=2;
        node<T> *parent = Q.front().first;
        k = Q.front().second;
        ld = 0;
        rd = 0;

        if(parent->left)
        {
            ld = getrd(parent->left);   ld*=3;
            /*switch(ld)
            {   case 0: ld = 1; break;
                case 1: ld = 3; break;
                default: ld*=pow(ratio, rd);
            }*/
            pair<node<T>*,int> P(parent->left, k - ld - 1);
            Q.push(P);  Q2.push(k - ld);
        }

        if(parent->right)
        {
            rd = getld(parent->right);  rd*=3;
            /*switch(rd)
            {   case 0: rd = 1; break;
                case 1: rd = 3; break;
                default: rd*=pow(ratio, rd);
            }*/
            pair<node<T>*,int> P(parent->right, k + rd + 1);
            Q.push(P);  Q2.push(k + rd + 2);
        }

        gotoxy(k - ld + 1, y);
        fill(ld , '-');
        cout<<parent->data;
        fill(rd , '-');

        Q.pop();

        parent = Q.front().first;
        if(parent==NULL)
        {
            Q.pop();
            if(Q.front().first!=NULL)
            {
                Q.push(PNULL);
                y++;
                while(Q2.empty()==false)
                {
                    gotoxy(Q2.front(), y);
                    cout<<'|';
                    Q2.pop();
                }
                y++;
                cout<<endl;
            }
        }

    }
    cout<<endl<<endl;
}



template <typename T>
void binarytree<T>::prettyprint()
{
    int k=pow(2, getd(root)), ld=0, rd=0, sub = 0;      if(getd(root)>5) k-=20;
    int x, y=gety() + 1;
    float ratio = 0.8 + (float)getd(root)/10;
    queue< pair<node<T>*, int> > Q;
    queue<int> Q2;

    pair<node<T>*,int> Proot(root, k);
    pair<node<T>*,int> PNULL(NULL, 0);      //CHECK if without 0

    Q.push(Proot);
    Q.push(PNULL);

    while(Q.empty()==false)
    {
        node<T> *parent = Q.front().first;
        k = Q.front().second;
        ld = 0;
        rd = 0;

        if(parent->left)
        {
            ld = getd(parent->left);
            ld==2?ld=3:ld*=pow(ratio, ld);
            pair<node<T>*,int> P(parent->left, k - ld - 1);
            Q.push(P);  Q2.push(k - ld);
        }

        if(parent->right)
        {
            rd = getd(parent->right);
            rd==2?rd=3:rd*=pow(ratio, rd);
            pair<node<T>*,int> P(parent->right, k + rd + 1);
            Q.push(P);  Q2.push(k + rd + 2);
        }
        //waitkey();
        gotoxy(k - ld + 1, y);
        fill(ld , '_');
        cout<<parent->data;
        fill(rd , '_');

        Q.pop();

        parent = Q.front().first;
        if(parent==NULL)
        {
            Q.pop();
            if(!Q.empty() && Q.front().first!=NULL)
            {
                Q.push(PNULL);
                y++;
                while(Q2.empty()==false)
                {
                    gotoxy(Q2.front(), y);
                    cout<<'|';
                    Q2.pop();
                }
                y++;
                cout<<endl;
            }
        }
    }
    cout<<endl<<endl;
}

#endif
