#ifndef BINARYTREE_FUNCTIONS_H_INCLUDED
#define BINARYTREE_FUNCTIONS_H_INCLUDED
#include "binary tree.h"

template <typename T>
void binarytree<T>::iterative_inorder()
{
    stack<node<T>*> S;
    S.push(NULL);
    if(root->right) S.push(root->right);
    if(root) S.push(root);
    if(root->left) S.push(root->left);

    while(S.empty()==false)
    {
        if(S.top()==NULL)
        {   S.pop();
            continue;
        }
        node<T> *curr = S.top();
        S.pop();

        if(curr->right == S.top())
        {   cout<<curr->data<<' ';
            continue;
        }

        S.push(curr->right);
        S.push(curr);
        S.push(curr->left);
    }
}


template <typename T>
void binarytree<T>::iterative_postorder()
{
    stack< pair<node<T>*,bool> > S;
    pair<node<T>*,bool> Pinit(root,0);
    S.push(Pinit);

    while(S.empty()==false)
    {
        node<T>* parent = S.top().first;
        if(S.top().second==0 && parent)
        {   S.top().second=1;
            pair<node<T>*,bool> Pright(parent->right,0);
            S.push(Pright);
            pair<node<T>*,bool> Pleft(parent->left,0);
            S.push(Pleft);
        }
        else
        {   if(parent)
                cout<<parent->data<<' ';
            S.pop();
        }
    }
}


void print(const char *start, const char *end)
{
    while(start<=end)
    {   cout<<*start;
        start++;
    }
}


template <typename T>
node<T>* binarytree<T>::in_and_post_order(node<T>* parent, const char *istart, const char *iend, const char *pstart, const char *pend)
{
    if(pstart>pend)
    {   return NULL;}

    parent = new node<T>(*pend - '0');
    const char* trav = istart;
    int count = 0;

    while(*trav!=*pend)
    {   trav++;
        count++;
    }

    //cout<<"\n\n\n"<<parent->data<<"\nLEFT:";cout<<"\nIn: ";print(istart, istart+count-1);cout<<"\nPost: ";print(pstart, pstart+count-1);cout<<"\n\nRIGHT:";cout<<"\nIn: ";print(istart+count+1, iend);cout<<"\nPost: ";print( pstart+count, pend-1);
    parent->left =  in_and_post_order(parent->left, istart, istart+count-1, pstart, pstart+count-1);
    parent->right = in_and_post_order(parent->right, istart+count+1, iend, pstart+count, pend-1);
    return parent;
}


template <typename T>
int binarytree<T>::diameter(T d = -1)
{
    if(d==-1)
    {   return getd(root->left) + getd(root->right) + 1;}
    else
    {   return diameter(root, d);}
}

template <typename T>
int binarytree<T>::diameter(node<T> *root, T d)
{
    if(!root)
        return 0;
    if(root->data==d)
        return getd(root->left) + getd(root->right) + 1;
    return diameter(root->left, d) + diameter(root->right, d);
}


template <typename T>
node<T>* binarytree<T>::delete_half_nodes(node<T> *parent)
{
    if(!parent->left && !parent->right)
    {   return parent;}

    if(parent->left && parent->right)
    {   cout<<":p:"<<parent->data<<' ';
        parent->left = delete_half_nodes(parent->left);
        parent->right = delete_half_nodes(parent->right);
        return parent;
    }
    node<T> *temp;

    if(parent->left)
    {   temp = parent->left;cout<<":l:"<<parent->data<<' ';
        delete parent;
        return delete_half_nodes(temp);
    }
    else
    {   temp = parent->right;cout<<":r:"<<parent->data<<' ';
        delete parent;
        return delete_half_nodes(parent->right);
    }
}


template <typename T>
node<T>* binarytree<T>::remove_leaf(node<T> *parent)
{
    if(!parent)
    {   return NULL;}

    if(!parent->left && !parent->right)
    {   delete parent;
        return NULL;
    }
    parent->left=remove_leaf(parent->left);
    parent->right=remove_leaf(parent->right);
    return parent;
}


template <typename T>
bool binarytree<T>::checkequal(const node<T> *p1, const node<T>* p2)
{
    if(!p1 && !p2)
    {   return 1;}

    if(!p1 || !p2)
    {   return 0;}

    if(p1->data != p2->data)
    {   return 0;}

    return checkequal(p1->left, p2->left) && checkequal(p1->right, p2->right);
}


template <typename T>
int binarytree<T>::isbalanced(node<T> *parent)
{
    if(!parent)
    {   return 0;}

    int l = isbalanced(parent->left);
    int r = isbalanced(parent->right);

    if(abs(l-r)>1)
    {   return -5;}

    return max(l,r) + 1;
}


template <typename T>
void binarytree<T>::sibling(const node<T> *parent)
{
    if(!parent)
    {   return;}

    if(!parent->left && !parent->right)
    {   return;}

    if(!parent->left || !parent->right)
    {   cout<<parent->data<<' ';}

    sibling(parent->left);
    sibling(parent->right);
}


template <typename T>
bool binarytree<T>::root_to_leaf( const node<T> *parent, int sum, const int &num)
{
    if(parent==NULL)
    {   return 0;}

    if(!parent->left && !parent->right)
    {   return  sum + parent->data == num ? 1:0;}

    sum+=parent->data;
    return root_to_leaf(parent->left, sum, num) || root_to_leaf(parent->right, sum, num);
}


template <typename T>
void swap(const node<T>* &left, const node<T>* &right)
{
    node<T>* temp = left;
    left = right;
    right = temp;
}

template <typename T>
void binarytree<T>::mirror(node<T> *parent)
{
    if(parent==NULL)
    {   return;}

    swap(parent->left, parent->right);
    mirror(parent->left);
    mirror(parent->right);
}

template <typename T>
vector<T> binarytree<T>::max_root_to_leaf()
{
     pair< T, vector<T> > P = max_root_to_leaf(root);
     return P.second;
}

template <typename T>
pair< T,vector<T> > binarytree<T>::max_root_to_leaf(node<T> *parent)
{
    if(!parent)
    {   vector<T> V;
        pair< T, vector<T> > P(0,V);
        return  P;
    }

    if(!parent->left && !parent->right)
    {   vector<T> V;
        V.push_back(parent->data);
        pair< T, vector<T> > P(V.at(0),V);      //CHANGE
        return P;
    }

    pair< T, vector<T> > Pleft = max_root_to_leaf(parent->left);
    pair< T, vector<T> > Pright = max_root_to_leaf(parent->right);

    if(Pleft.second.empty() || (!Pright.second.empty() && Pleft.first<Pright.first))
    {   Pright.first+=parent->data;
        Pright.second.push_back(parent->data);
        return Pright;
    }
    else
    {   Pleft.first+=parent->data;
        Pleft.second.push_back(parent->data);
        return Pleft;
    }
}


template <typename T>
int binarytree<T>::same_level(const node<T> * const parent)
{
    if(!parent->left && !parent->right)
    {   return 0;}

    if(!parent->left || !parent->right)
    {
        if(!parent->left)
        {   int r = same_level(parent->right);
            return r==-1 ? -1: r+1;
        }
        else
        {   int l = same_level(parent->left);
            return l==-1 ? -1: l+1;
        }
    }

    int l=same_level(parent->left);
    int r=same_level(parent->right);

    if(l==-1 || r==-1 || l!=r)
    {   return -1;}

    return l+1;
}


template <typename T>
bool binarytree<T>::check_sum(const int &num)
{
    unordered_set<T> H;
    return check_sum(root,H,num);
}

template <typename T>
bool binarytree<T>::check_sum(node<T>* parent, unordered_set<T> &H, const int &num)
{
    if(!parent)
    {   return 0;}

    if(H.find(num - parent->data)!=H.end())
    {   return 1;}

    H.insert(parent->data);
    return check_sum(parent->left,H,num) || check_sum(parent->right,H,num);
}


#endif // BINARYTREE_FUNCTIONS_H_INCLUDED
