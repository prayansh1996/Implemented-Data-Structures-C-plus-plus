#ifndef TREE_FUNCTIONS_H_INCLUDED
#define TREE_FUNCTIONS_H_INCLUDED
#include "tree.h"

template <typename T>
ostream& operator<<(ostream& out, const tree<T> &temp)
{   temp.pretty_print();
    return out;
}


template <typename T>
void tree<T>::print_at_depth(int kmain)
{
    int k = kmain, i;
    queue<const node<T>*> Q;
    Q.push(root);

    for(k; k>0; k--)
    {   const node<T> *parent = Q.front();
        for(i=0; i<parent->child.size(); i++)
        {   if(k == 1)
            {   cout<<parent->data<<' ';}
            else
            {   Q.push(parent->child.at(i));}
        }
        Q.pop();
    }
}


template <typename T>
int tree<T>::count_root(const node<T> *parent, T root)
{
    int count = 0;
    for(int i=0; i<parent->child.size(); i++)
    {   count+= count_root(parent->child.at(i), root);}

    if(parent->data > root)
        return count + 1;
    return count;
}


template <typename T>
int tree<T>::count_leaf(const node<T> *parent)
{
    if(parent->child.size()==0)
    {   return 1;}

    int count = 0;
    for(int i=0; i<parent->child.size(); i++)
    {   count+= count_leaf(parent->child.at(i));}

    return count;
}


template <typename T>
node<T>* tree<T>::max_sum(node<T> *parent, int &maxsum, int &sum)
{
    if(parent->child.size()==0)
    {   sum = parent->data;
        if(sum>maxsum)
        {   maxsum = sum;
            return parent;
        }
        return NULL;
    }

    int curr_sum=parent->data;
    node<T>* temp = NULL, *max_node = NULL;

    for(int i=0; i<parent->child.size(); i++)
    {   temp = max_sum(parent->child.at(i), maxsum, sum);
        if(temp)
        {   max_node = temp;}
        curr_sum = curr_sum + sum;
    }
    sum = curr_sum; if(temp!=NULL){ cout<<"wohoo!";}

    if(sum > maxsum)
    {   maxsum = sum;
        return parent;
    }
    return max_node;
}


template <typename P>
void tree<P>::operator=(const tree<P> &T)
{
    node<P> *temp = new node<P>(T.root->data);
    root = temp;
    copy_tree(root, T.root);
}


template <typename T>
void tree<T>::copy_tree(node<T> *parent, const node<T> *cparent)
{
    if(cparent->child.size()==0)
       return;

    for(int i=0; i<cparent->child.size(); i++)
    {   node<T> *temp = new node<T>(cparent->child.at(i)->data);
        temp->parent = parent;
        parent->child.push_back(temp);
        copy_tree(parent->child.at(i), cparent->child.at(i));
    }
}


template <typename T>
pair<node<T>*,node<T>*> tree<T>::second_largest(node<T> *parent)
{
    if(parent->child.size()==0)
    {   pair<node<T>*,node<T>*> Pchild(parent, NULL);
        return Pchild;
    }

    pair<node<T>*,node<T>*> P = second_largest(parent->child.at(0));
    if(parent->data > P.first->data)
    {   P.second = P.first;
        P.first = parent;
    }
    else if(P.second && P.second->data > parent->data)
    {   /*DO NOTHING*/}
    else
    {   P.second = parent;}

    for(int i=1; i<parent->child.size(); i++)
    {   pair<node<T>*,node<T>*> Pchild = second_largest(parent->child.at(i));
        if(Pchild.first->data > P.first->data)
        {
            P.second = P.first;
            P.first = Pchild.first;
            if(Pchild.second && Pchild.second->data > P.second->data)
            {   P.second = Pchild.second;   }
        }
        else if(Pchild.first->data > P.second->data)
        {   P.second = Pchild.first;    }
    }

    return P;
}


template <typename T>
void tree<T>::iterative_postorder()
{
    stack< pair<node<T>*,bool> > S;
    pair<node<T>*,bool> Pinit(root,0);
    S.push(Pinit);

    while(S.empty()==false)
    {
        if(S.top().second==1)
        {   cout<<S.top().first->data<<' ';
            S.pop();
        }
        else
        {   S.top().second=1;
            node<T> *parent=S.top().first;
            for(int i=parent->child.size()-1; i>=0; i--)
            {   pair<node<T>*,bool> P(parent->child.at(i),0);
                S .push(P);
            }
        }
    }
}


template <typename T>
void tree<T>::zigzag()
{
    stack<node<T>*> Q;
    stack<node<T>*> S;
    Q.push(root);
    bool ch=1;

    while(Q.empty()==false || S.empty()==false)
    {
        node<T>* parent=NULL;

        if(ch==1)
        {   while(Q.empty()==false)
            {   parent = Q.top();
                cout<<"\n"<<parent->data<<' ';
                Q.pop();
                for(int i=0; i<parent->child.size(); i++)
                {   S.push(parent->child.at(i));}
            }
            ch=0;
        }
        else
        {   while(S.empty()==false)
            {   parent = S.top();
                cout<<"\n"<<parent->data<<' ';
                S.pop();
                for(int i=parent->child.size()-1; i>=0; i--)
                {   Q.push(parent->child.at(i));}
            }
            ch=1;
        }
    }
}

/*
template <typename T>
node<T>* tree<T>::justLargerThanK(node<T> *parent, const T &k)
{
    if(!parent)
    {   return NULL;}

    node<T> *left = justLargerThanK(parent->left, k);
    node<T> *right = justLargerThanK(parent->right, k);

    if(!left && !right)
    {   if(parent->data>k)
        {   return parent;}
        else
        {   return NULL;}
    }

    if(!left)
    {   if(parent->data<k && right->data<k)
        {   return NULL;}
        if(parent->data<k)
        {   return right;}
        if(right->data<k)
        {   return parent;}

        if(parent->data>right->data)
        {   return right;}
        else
        {   return parent;}
    }

     if(!right)
    {   if(parent->data<k && left->data<k)
        {   return NULL;}
        if(parent->data<k)
        {   return left;}
        if(left->data<k)
        {   return parent;}

        if(parent->data>left->data)
        {   return left;}
        else
        {   return parent;}
    }

}*/



#endif // TREE_FUNCTIONS_H_INCLUDED
