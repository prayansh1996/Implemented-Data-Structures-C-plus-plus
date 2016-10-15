#ifndef MYNODE_H_INCLUDED
#define MYNODE_H_INCLUDED
#include <iostream>
using namespace std;
class linkedlists;
ostream& operator<<(ostream &obj, const linkedlists &L);

struct node
{
    private:
    node *next;
    int data;
    friend class linkedlists;

    public:
    node();
    node(int);
    ~node();
    node* getnext();
    void setnext(node*);
    int getdata();
    void setdata(int);
};

class linkedlists
{
    node *head;
    public:
    linkedlists();
    ~linkedlists();
    linkedlists(const linkedlists&);
    void insert_end(int);
    void printlist();
    void delete_end();
    void makelist();
    void make_unsorted_list();

    // Swap ith and jth Node of the linked list - Swap Nodes not the data. Do nothing if I or J are out of bounds
    void swap_nodes(int i, int j);

    // Reverses the linked list. Not print in reverse order.
    void reverse();

    // Sort the linked list using selection sort.
    void ssort();   node* insert_smallest(node*, node*);

    //Return Mid Element
    void return_mid(node* &even, node* &odd);

    //Check if the list is a palindrome
    bool palindrome();

    // Rearrange the nodes such that all even elements are after odd elements. Again you need change next pointers not the data
    void whataretheodds();
    void makeoddlist(node* curr, node* &oddhead, node* &trav);

    //Rotate the linked list
    void rotatelist(int);

    // Remove Duplicates From the sortedList.
    // This function assumes the linked list is sorted and deletes duplicated nodes from the linked list.
    void removeDuplicatesFromSorted();

    // Rotate Linked List By K. You need to clockwise rotate the linked list by K. E.g. 1->2->3->4->5->6null and if K was 2 linked list should become 5->6->1->2->3->4->null
    void kreverse(int);

    linkedlists& operator+=(const linkedlists &L2);
    friend ostream& operator<<(ostream &obj, const linkedlists &L);

    node* getmid(node*,node*);
    node* gethead();
    node* getlast();
    pair<node*,node*> sort_func(node *start1, node *last1, node *start2, node *last2);
    pair<node*,node*> mergesort(node *start, node *last);
};

//NODE FUNCTIONS
node :: node()
{
    next = NULL;
}

node::node(int d)
{
    next = NULL;
    data = d;
}

node::~node()
{    cout<<"\nNode Destructed\n";}

node* node::getnext()
{   return next;}

void node::setnext(node *n)
{   next = n;}

int node::getdata()
{   return data;}

void node::setdata(int d)
{   data = d;}


//LINKEDLISTS FUNCTIONS
linkedlists::linkedlists()
{   head = NULL;}

linkedlists::~linkedlists()
{
    node *temp;
    while(head)
    {   temp = head->getnext();
        delete head;
        head = temp;
    }cout<<"\nLinkedList Destroyed\n";
}

void linkedlists::insert_end(int d)
{
    node *temp = new node(d);   //Temp->next=NULL Temp->data=d

    if(head==NULL)
    {   head = temp;
        return;
    }

    node *trav = head;
    while(trav->getnext())
    {   trav = trav->getnext();}
    trav->setnext(temp);
}

void linkedlists::printlist()
{
    node *trav = head;
    cout<<endl;
    while(trav)
    {   cout<<trav->getdata()<<"->";
        trav = trav->getnext();
    }cout<<"NULL\n";
}

void linkedlists::delete_end()
{
    if(head==NULL)
    {   return;}

    node *curr = head, *prev = NULL;
    while(curr->getnext())
    {   prev = curr;
        curr = curr->getnext();
    }
    if(prev==NULL)
    {   head = NULL;}
    else
    {   prev->setnext(0);}

    delete curr;
}

linkedlists::linkedlists(const linkedlists &L2)
{
    head = NULL;
    node *trav = L2.head;
    node *prev = NULL;

    while(trav)
    {   node *temp = new node(trav->getdata());
        temp->setnext(NULL);
        if(head==NULL)
        {   head = temp; }
        else{   prev->setnext(temp);}
        prev = temp;
        trav = trav->getnext();
    }
}

void linkedlists::makelist()
{
    for(int i=1; i<10; i++)
    {   insert_end(i);}
}

void linkedlists::make_unsorted_list()
{
    insert_end(7);insert_end(2);insert_end(5);insert_end(1);insert_end(4);insert_end(6);insert_end(3);
}

ostream& operator<<(ostream &obj, const linkedlists &L)
{
    node *temp = L.head;
    while(temp)
    {   obj<<temp->getdata()<<"->";
        temp = temp->getnext();
    }obj<<"NULL";
    return obj;
}

node* linkedlists::getmid(node* start, node *last)
{
    node *mid = start;
    node *temp = start;

    bool x=0;

    while(temp!=last->next)
    {
        temp = temp->next;
        if(temp!=last->next && x == 1)
        {   mid = mid->next;}
        x = 1-x;
    }
    return mid;
}

node* linkedlists::gethead()
{   return head;}

node* linkedlists::getlast()
{
    node *temp = head;
    while(temp->next)
    {   temp = temp->next;}
    return temp;
}

bool linkedlists::palindrome()
{
    node *templ = head, *tempr = head;
    int l=0, r;

    while(templ)
    {   l++;
        templ = templ->getnext();
    }

    if(l%2==1)
    {   r = l/2 + 2;
        l = l/2;
    }
    else
    {   r = l/2 + 1;
        l = l/2;
    }

    while(--r)
    {   tempr = tempr->getnext();}
    while(tempr)
    {   int lcopy = l;
        templ = head;
        while(--lcopy)
        {   templ = templ->getnext();}
        if(templ->getdata() != tempr->getdata())
        {   return false;}
        l--;
        tempr = tempr->getnext();
    }
    return true;
}

void linkedlists::kreverse(int k)
{
    if(k==0 || k==1)
    {   return;}

    node *prev = head, *curr = prev->getnext(), *temp = curr->getnext();
    node *nextk = NULL, *start = NULL;
    int kcopy = k;
    while(--kcopy)
    {   head = head->getnext();}

    while(temp)
    {
        kcopy = k;
        start = prev;
        while(--kcopy || curr!=NULL)
        {   curr->setnext(prev);
            prev = curr;
            curr = temp;
            if(temp)
            {   temp = temp->getnext();}
        }

        kcopy = k;
        nextk = curr;
        while(--kcopy && nextk->getnext()!=NULL)
        {   nextk = nextk->getnext();}
        start->setnext(nextk);

        prev = curr;
        curr = temp;
        if(temp!=NULL)
        {   temp = temp->getnext();}
    }
}

void linkedlists::makeoddlist(node* curr, node* &oddhead, node* &trav)
{
    if(oddhead==NULL)
    {
        oddhead = trav = curr;
        trav->setnext(NULL);
    }
    trav->setnext(curr);
    trav = curr;
    trav->setnext(NULL);
}

void linkedlists::whataretheodds()
{
    node *oddhead = NULL, *trav;int i=1;
    node *prev, *curr=head;

    while(curr)
    {   if(curr->getdata()%2==0)
        {
            prev = curr;
            curr = curr->getnext();
        }
        else
        {
            if(prev==NULL)
            {
                head = head->getnext();
                makeoddlist(curr, oddhead, trav);
                curr = head;
            }
            else
            {
                if(curr->getnext()==NULL)
                {
                    prev->setnext(NULL);
                }
                else
                {
                    prev->setnext(curr->getnext());
                }
                makeoddlist(curr, oddhead, trav);
                curr = prev->getnext();
            }
        }
    }prev->setnext(oddhead);
}

void linkedlists::removeDuplicatesFromSorted()
{
    if(head == NULL || head->getnext() == NULL)
    {   return;}

    node *prev=head, *curr=head->getnext();
    while(curr)
    {   if(prev->getdata()!=curr->getdata())
        {   prev = curr;
            curr = curr->getnext();
        }
        else
        {
            prev->setnext(curr->getnext());
            delete curr;
            curr = prev->getnext();
        }
    }
}

void linkedlists::return_mid(node* &even, node* &odd)
{
    int l = 0;
    even = odd = NULL;
    node* temp = head;

    while(temp!=NULL)
    {   temp = temp->getnext();
        l++;
    }temp = head;

    if(l%2==1)
    {   l/=2;
        while(l--)
        {   temp = temp->getnext();}
        odd = temp; cout<<"\nMid = "<<odd->getdata()<<"\t Even pointer is NULL\n";
    }

    else
    {   l/=2;
        while(l--)
        {   if(l==0)
            {   even = temp;}
            temp = temp->getnext();
        }odd = temp;cout<<"\nEven Mid = "<<even->getdata()<<"\tOdd Mid = "<<odd->getdata()<<"\n";
    }
}

void linkedlists::reverse()
{
     if(head==NULL || head->getnext()==NULL)
     {  return;}

     node *prev = head, *curr = prev->getnext(), *temp = curr->getnext();
     prev->setnext(0);

     while(curr!=NULL)
     {  curr->setnext(prev);
        prev = curr;
        curr = temp;
        if(temp!=NULL)
        {   temp = temp->getnext();}
     }
     head = prev;
}

void linkedlists::rotatelist(int k)
{
    node *last = head, *prev = head;
    int l=1;

    while(last->getnext()!=NULL)
    {   l++; last = last->getnext();}

    if(k%l==0)
    {   return;}

    if(k>l)
    {   k = k%l;}
    k = l-k;

    while(--k)
    {   prev = prev->getnext();}
    last->setnext(head);
    head = prev->getnext();
    prev->setnext(NULL);
}

void linkedlists::ssort()
{
    node *smallest, *smallest_prev;
    node *curr, *prev;
    node *trav, *temp, *headcopy = head;
    head=NULL;

    while(headcopy!=NULL)
    {   smallest = curr = headcopy;
        smallest_prev = prev = NULL;
        while(curr!=NULL)
        {   if(curr->getdata()<smallest->getdata())
            {   smallest = curr;
                smallest_prev = prev;
            }
            prev = curr;
            curr = curr->getnext();
        }
        if(smallest_prev==NULL)
        {   temp = headcopy;
            headcopy = headcopy->getnext();
            trav = insert_smallest(temp, trav);
        }
        else
        {   if(smallest->getnext()==NULL)
            {   smallest_prev->setnext(NULL);}
            else
            {   smallest_prev->setnext(smallest->getnext());}
            trav = insert_smallest(smallest, trav);
        }
    }
}

node* linkedlists::insert_smallest(node* smallest, node* trav)
{
    if(head==NULL)
    {   head = trav = smallest;
        trav->setnext(NULL);
        return trav;
    }
    trav->setnext(smallest);
    trav = smallest;
    trav->setnext(NULL);
    return trav;
}

void linkedlists::swap_nodes(int i, int j)
{
    if(i==j){   return;}
    node *iprev = NULL, *icurr = head;
    node *jprev = NULL, *jcurr = head;
    node *temp;

    while(icurr->getdata()!=i)
    {   iprev = icurr;
        icurr = icurr->getnext();
    }
    while(jcurr->getdata()!=j)
    {   jprev = jcurr;
        jcurr = jcurr->getnext();
    }

    if(iprev)   {   iprev->setnext(jcurr);}
    else        {   head = jcurr;}
    if(jprev)   {   jprev->setnext(icurr);}
    else        {   head = icurr;}

    temp = icurr->getnext();
    icurr->setnext(jcurr->getnext());
    jcurr->setnext(temp);
}
#endif // MYNODE_H_INCLUDED
