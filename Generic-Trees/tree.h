#ifndef Gtrees_Header_h
#define Gtrees_Header_h
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

using namespace std;
template <typename T>   class tree;


template <typename T>
class node
{
 public:
    T data;
    vector<node*> child;
    node *parent;

    node(): parent(NULL), data(0){}
    node(T d): parent(NULL), data(d){}
    template <typename P> friend class tree;
    template <typename P>  friend ostream& operator<<(ostream&, const tree<P>&);
};

template <typename T>
class tree
{
    node<T> *root;
    //DELETE
    static void delete_tree(node<T>*);

    //CREATE TREES
    static void create_tree_by_branch(node<T>*);
    static void copy_tree(node<T>*, const node<T>*);

    //PRINT
    static void pretty_print(const node<T>*,int);
    //Order = 0 for preorder, order = 1 for postorder. NOTE: Generic trees don't have any inorder traversal
    static void print(const node<T>*, const int& order);
    static int print_height(const node<T>*);
    static const char& print_max(const node<T>*);

    //OTHERS
    static int count_root(const node<T>*, T);
    static int count_leaf(const node<T>*);
    static node<T>* max_sum(node<T>*, int&, int&);
    static pair<node<T>*,node<T>*> second_largest(node<T>*);
    static int isequal(node<T>*, node<T>*);
    //static node<T> * justLargerThanK(node<T>*, const T &k);

    public:
    tree(): root(NULL){}
    //DESTRUCTORS
    ~tree();
    void clear_tree(){  delete_tree(root);}
    //CREATE TREES
    void create_tree_by_depth();
    void create_tree_by_branch();
    void maketree(T);
    //PRINT
    void pretty_print() const  {   pretty_print(root, 0);}
    void print_postorder()  {   print(root, 1);}
    void print_preorder()   {   print(root, 0);}
    void print_by_level();
    int print_height()     {   return print_height(root);}
    const char& print_max(){   return print_max(root);}
    template <typename P>  friend ostream& operator<<(ostream&, const tree<P>&);
    void print_at_depth(int k);
    int count_root() { return count_root(root, root->data);}
    int count_leaf() { return count_leaf(root);}
    node<T>* max_sum()    { int maxsum=0, sum=0;   return max_sum(root, maxsum, sum);}
    void operator=(const tree<T>&);
    void print_data(node<T> *temp){    cout<<temp->data;}
    int second_largest()  {     return second_largest(root).second->data;}
    bool isequal(const tree &T1, const tree &T2)  {   return T1.root==T2.root? isequal(T1.root, T2.root)+1%2: 1;}
    void iterative_postorder();
    void zigzag();
    //node<T> * justLargerThanK(const T &k)   {   node<T> *temp = justLargerThanK(root,k);    cout<<temp->data;}
};


template <typename T>
void print(queue<T> Q)
{
    cout<<endl<<"Q: ";
    while(Q.empty()==false)
    {   cout<<Q.front()->data<<' '; Q.pop();}
    cout<<endl;
}


//TREE FUNCTIONS
template <typename T>
tree<T>::~tree()
{   delete_tree(root);}


template <typename T>
void tree<T>::delete_tree(node<T> *root)
{
    if(root == NULL)
    {   return;}

    for(int i=0; i<root->child.size(); i++)
    {   delete_tree(root->child.at(i));}

    delete root;
}


template <typename T>
void tree<T>::create_tree_by_depth()       //CREATE BY ONE DEPTH AT A TIME
{
    T d=0;
    queue<node<T> *> Q;

    cout<<"Enter Root :";
    cin>>d;
    node<T> *temp = new node<T>(d);
    root = temp;
    Q.push(root);

    while(Q.empty()==false)
    {
        node<T> *curr_parent = Q.front();
        cout<<"Enter Data of "<<curr_parent->data<< "'s Children: ";

        while(1)
        {
            cin>>d;
            if(d == -10)
            {   break;}

            node<T> *temp = new node<T>(d);
            curr_parent->child.push_back(temp);
            temp->parent = curr_parent;

            Q.push(temp);
        }

        Q.pop();
    }
}


template <typename T>
void tree<T>::pretty_print(const node<T>* curr_parent, int depth)
{
    if(curr_parent == NULL)
        return;

    int i = depth;
    while(i--)
    {   cout<<".  ";}
    cout<<"\\_";

    cout<<curr_parent->data<<endl;

    for(i=0; i<curr_parent->child.size(); i++)
    {   pretty_print(curr_parent->child.at(i), depth + 1);}
}


template <typename T>
void tree<T>::maketree(T d)
{
    T ch = d;
    int i;
    node<T> *rinit = new node<T>(ch);   ch++;
    root = rinit;

    node<T> *curr_parent = root, *curr_child = NULL;

    for(i=0; i<3; i++)
    {
        node<T> *temp = new node<T>(ch);    ch++;
        curr_parent->child.push_back(temp);
        temp->parent = curr_parent;
    }

    for(i=0; i<3; i++)
    {
        curr_child = curr_parent->child.at(i);

        for(int j = 2-i; j>0; j--)
        {
            node<T> *temp = new node<T>(ch++);
            curr_child->child.push_back(temp);
            temp->parent = curr_child;
        }
    }

    curr_parent = curr_parent->child.at(0);     //AT C
    curr_parent = curr_parent->child.at(1);     //AT G

    for(i=0; i<2; i++)
    {
        node<T> *temp = new node<T>(ch++);
        curr_parent->child.push_back(temp);
        temp->parent = curr_parent;
    }
}


template <typename T>
void tree<T>::create_tree_by_branch()
{
    T d;
    cout<<"Enter Data :";
    cin>>d;
    node<T> *temp = new node<T>(d);
    root = temp;

    create_tree_by_branch(root);
}


template <typename T>
void tree<T>::create_tree_by_branch(node<T> *parent)
{
    int i=1;
    T d;
    cout<<endl;
    while(1)
    {   cout<<"Enter "<<parent->data<<"'s "<<i<<" child: ";
        cin>>d;

        if(d == '0')
        return;

        node<T> *temp = new node<T>(d);
        parent->child.push_back(temp);
        temp->parent = parent;
        create_tree_by_branch(temp);
    }
}

template <typename T>
void tree<T>::print(const node<T> *parent, const int &order)
{
    if(order==0)
    {   cout<<parent->data<<' ';}

    for(int i=0; i<parent->child.size(); i++)
        print(parent->child.at(i), order);

    if(order==1)
    {   cout<<parent->data<<' ';}
}


template <typename T>
void tree<T>::print_by_level()
{
    queue<node<T>*> Q;
    Q.push(root);

    while(Q.empty()==false)
    {
        node<T> *parent = Q.front();
        for(int i=0; i<parent->child.size(); i++)
        {   Q.push(parent->child.at(i));}

        cout<<parent->data<<' ';
        Q.pop();
    }
}


template <typename T>
int tree<T>::print_height(const node<T> *parent)
{
    if(parent->child.size()==0)
    {   return 0;}

    int maxh=0;
    for(int i=0; i<parent->child.size(); i++)
    {   maxh = max( print_height(parent->child.at(i)) + 1, maxh);}

    return maxh;
}


template <typename T>
const char& tree<T>::print_max(const node<T> *parent)
{
    if(parent->child.size()==0)
    {   return parent->data;}

    char maxh=0;
    for(int i=0; i<parent->child.size(); i++)
    {   maxh = max( print_max(parent->child.at(i)), maxh);
        maxh = max( parent->data, maxh);
    }

    return maxh;
}

#endif
