#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

template <typename T>   class queue;
template <typename T>   std::ostream& operator<<(std::ostream&, const queue<T> &Q);

template <typename T>
class node
{
    T data;
    node *next;
    template <typename type> friend std::ostream& operator<<(std::ostream&, const queue<type> &Q);

    public:
    node(): data(0), next(NULL){}
    node(const T &d): data(d), next(NULL){}
    template <typename type>   friend class queue;
};


template <typename T>
class queue
{
    node<T> *front;
    node<T> *rear;

    public:
    queue(): front(NULL), rear(NULL){}
    ~queue();
    void enqueue(const T&);
    T dequeue();
    template <typename type> friend std::ostream& operator<<(std::ostream&, const queue<type> &Q);
};


//QUEUE FUNCTIONS

template <typename T>
queue<T>::~queue()
{
    std::cout<<"\nQueue Finished\n";
    while(rear)
    {   delete rear;
        rear = rear->next;
    }
}


template <typename T>
void queue<T>::enqueue(const T& d)
{
    node<T> *temp = new node<T>(d);

    if(front == NULL)
    {   front = rear = temp;
        return;
    }

    rear->next = temp;
    rear = temp;
}


template <typename T>
T queue<T>::dequeue()
{
    T data = front->data;
    node<T> *temp = front->next;

    delete front; front = NULL;

    front = temp;
    return data;
}


template <typename T>
std::ostream& operator<<(std::ostream& out, const queue<T> &Q)
{
    const node<T> *trav = Q.front;
    out<<std::endl;
    while(trav)
    {   out<<trav->data;
        if(trav->next)
        {   out<<"<-";}
        trav = trav->next;
    }out<<std::endl;

    return out;
}

#endif // QUEUE_H_INCLUDED
