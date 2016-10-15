#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include <iostream>
//#include <iomanip>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_set>
#include "misc.h"
#include <cmath>

using namespace std;
template <typename T> class BST;

template <typename T>
class node
{
    node *left;
    node *right;
    T data;
    template <typename B> friend class BST;

public:
    node(): left(0), right(0), data(0){}
    node(T d): left(0), right(0), data(d){}
};


template <typename T>
class BST
{
    node<T> *root;
    void static clearBST(node<T>*);
    static node<T>* insert_ele(node<T>*, const T&);
    static int getd(node<T>*);
    static int getlrd(node<T>*, char, char);
    static void order(const node<T>*, const char*);
    static node<T>* remove_ele(node<T>*, const T&);
    static const pair<const node<T>*, const node<T>*> sum_OhN(const node<T>*, const node<T>*, const T&);
    static node<T>* find_ele(node<T>*, const T &d);
    static T sumOfAllGreaterNodes(node<T>* const, T val);
    static pair<node<T>*,node<T>*> createDLL(node<T>*);
    static void printDLL(node<T>*);

public:
    BST(): root(0){}
    ~BST();
    void maketree();
    void insert_ele(const T &d)    {   if(root==NULL)  root = new node<T>(d); else root=insert_ele(root,d);}
    void delete_ele(const T &d);
    void prettyprint();
    int getld(node<T>* parent)  {   return getlrd(parent, 'n', 'l');}
    int getrd(node<T>* parent)  {   return getlrd(parent, 'n', 'r');}
    void order(const char *str) {   order(root, str);}
    T LCA(const T&, const T&);
    void remove_ele(const T &d) {   root = remove_ele(root, d);}
    void sum_OhN(const T&);
    void sum_logn(const T&);
    void sumOfAllGreaterNodes() {   sumOfAllGreaterNodes(root, 0);}
    void createDLL()    {   pair<node<T>*,node<T>*> P = createDLL(root);   root = P.first; printDLL(root);}
};


//BST FUNCTIONS
template <typename T>
pair<node<T>*,node<T>*> BST<T>::createDLL(node<T>* parent)
{
    if(!parent)
    {   pair<node<T>*,node<T>*> P(0,0);
        return P;
    }


    node<T> *head = NULL, *tail = NULL;
    pair<node<T>*,node<T>*> PL = createDLL(parent->left);
    pair<node<T>*,node<T>*> PR = createDLL(parent->left);

    if(PL.first==NULL)
    {   head = parent;}
    else
    {   head = PL.first;
        PL.second->right = parent;
        parent->left = PL.second;
    }

    if(PR.first==NULL)
    {   tail = parent;}
    else
    {   tail = PR.second;
        parent->right = PR.first;
        PR.first->left = parent;
    }

    pair<node<T>*,node<T>*> P(head,tail);
    return P;
}

template <typename T>
void BST<T>::printDLL(node<T>* parent)
{
    node<T> *trav = parent;
    while(trav)
    {   cout<<trav->data<<"->";
        trav = trav->right;
    }
}


template <typename T>
T BST<T>::sumOfAllGreaterNodes(node<T>* const parent, T val)
{
    if(!parent)
    {   return 0;}

    parent->data += val;
    parent->data += sumOfAllGreaterNodes(parent->right, val);
    sumOfAllGreaterNodes(parent->left, parent->data);
    return parent->data;
}


template <typename T>
node<T>* BST<T>::find_ele(node<T> *parent, const T &d)
{
    if(!parent)
    {   return NULL;}

    if(parent->data == d)
    {   return parent;}

    if(parent->data<d)
    {   return find_ele(parent->right, d);}

    if(parent->data>d)
    {   return find_ele(parent->left, d);}
}


template <typename T>
void BST<T>::sum_logn(const T &d)
{
    queue<node<T>*> Q;
    Q.push(root);

    while(Q.empty()==false)
    {
        node<T> *parent = Q.front();
        Q.pop();
        node<T> *s = find_ele(root, d - parent->data);

        if(s && s!=parent)
        {   cout<<"\n("<<parent->data<<","<<s->data<<")\n";
            return;
        }

        if(parent->left)
        {   Q.push(parent->left);}
        if(parent->right)
        {   Q.push(parent->right);}
    }
    cout<<"\nNO PAIR FOUND";
}


template <typename T>
void BST<T>::sum_OhN(const T &d)
{   pair< const node<T>*, const node<T>*> P1 = sum_OhN(root, root->right, d);
    pair< const node<T>*, const node<T>*> P2 = sum_OhN(root->left, root, d);
    if(!P1.first && !P2.first)
    {   cout<<"\nNO PAIR FOUND";
        return;
    }

    if(P1.first==NULL)
    {   cout<<"\n("<<P2.first->data<<","<<P2.second->data<<")\n";}
    else
    {   cout<<"\n("<<P1.first->data<<","<<P1.second->data<<")\n";}
}

template <typename T>
const pair<const node<T>*, const node<T>*> BST<T>::sum_OhN(const node<T>* left, const node<T>* right,const T &sum)
{
    if(!left || !right)
    {   pair<const node<T>*, const node<T>*>  P(0,0);         //CHECK WORKING
        return P;
    }

    int cs = left->data + right->data;
    //cout<<"\nThis: ("<<left->data<<","<<right->data<<")";

    if(cs==sum)
    {   pair<const node<T>*, const node<T>*> P(left, right);
        return P;
    }

    pair<const node<T>*, const node<T>*>  P1(0,0), P2(0,0), PNULL(0,0);

    if(cs<sum)
    {   if(left->right == right)
        {   P1 = sum_OhN(right->left, right, sum);}
        else
        {   P1 = sum_OhN(left->right, right, sum);}

        P2 = sum_OhN(left, right->right, sum);
    }

    if(cs>sum)
    {   if(right->left==left)
        {   P1 = sum_OhN(left, left->right, sum);}
        else
        {   P1 = sum_OhN(left, right->left, sum);}
        P2 = sum_OhN(left->left, right, sum);
    }

    if(!P1.first && !P2.first)
    {   return PNULL;}

    if(P1.first==NULL)
    {   return P2;}
    return P1;
}


template <typename T>
T BST<T>::LCA(const T &l, const T &r)
{
    node<T> *lca = root;
    while(lca)
    {   T data = lca->data;
        if(l<data && r<data)
        {   lca = lca->left;}
        else
        if(l>data && r>data)
        {   lca = lca->right;}
        else
        break;
    }
    if(lca)
    cout<<lca->data;
}

template <typename T>
BST<T>::~BST()
{
    if(root)
    {   clearBST(root);}
}

template <typename T>
void BST<T>::clearBST(node<T> *root)
{
    if(!root)
    {   return;}

    clearBST(root->left);
    clearBST(root->right);
    delete root;
}


template <typename T>
void BST<T>::maketree()
{
  insert_ele(6);
  insert_ele(9);
  insert_ele(1);
  insert_ele(7);
  insert_ele(5);
  insert_ele(3);
  insert_ele(4);
  insert_ele(10);
  insert_ele(0);
  insert_ele(2);
}


template <typename T>
node<T>* BST<T>::insert_ele(node<T> *root, const T &d)
{
    if(root==NULL)
    {   root = new node<T>(d);
        return root;
    }

    if(d<root->data)  root->left = insert_ele(root->left, d);
    else    root->right = insert_ele(root->right, d);
    return root;
}

template <typename T>
void BST<T>::order(const node<T> *root, const char *str)
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
node<T>* BST<T>::remove_ele(node<T>* parent, const T &d)
{
    if(!parent)
    {   return NULL;}

    if(parent->data==d)
    {
        if(!parent->left && !parent->right)
        {   delete parent;
            return NULL;
        }

        if(!parent->left || !parent->right)
        {   node<T> *child;
            if(parent->left)
            {   child = parent->left;}
            else
            {   child = parent->right;}

            delete parent;
            return child;
        }

        node<T> *p = parent->left;
        if(p->right == NULL)
        {   p->right = parent->right;
            delete parent;
            return p;
        }
        else
        {   node<T> *c = p->right;
            while(c->right)
            {   p = c;
                c = c->right;
            }
            p->right = c->left;
            c->left = parent->left;
            c->right = parent->right;
            delete parent;
            return c;
        }
    }

    if(d>parent->data)
    {   parent->right = remove_ele(parent->right, d);}
    else
    {   parent->left = remove_ele(parent->left, d);}

    return parent;
}

template <typename T>
int BST<T>::getd(node<T> *parent)
{
    if(parent == NULL)
        return 0;

    int l = getd(parent->left) + 1;
    int r = getd(parent->right) + 1;
    return max(l,r);
}


template <typename T>
int BST<T>::getlrd(node<T> *parent, char ch, char input)
{
    if(parent == NULL)
        return 0;

    int add=0;
    if(ch==input)
        add=1;

    return getlrd(parent->left, 'l', input) + getlrd(parent->right, 'r', input) + add;
}


template <typename T>
void BST<T>::prettyprint()
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

#endif // BST_H_INCLUDED
