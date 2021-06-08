#ifndef LIST_NODE_HH
#define LIST_NODE_HH

template <class T>
class ListNode
{
    ListNode *previous;
    T data;
    ListNode *next;

public:
    ListNode();
    ListNode(T data);
    ListNode(T data, ListNode *previous, ListNode *next);
    ~ListNode();

    void set_data(T elem);
    void set_previous(ListNode<T> *previous);
    void set_next(ListNode<T> *next);

    T *get_data();
    ListNode *get_previous();
    ListNode *get_next();

    template <class t>
    friend bool operator==(const ListNode<t> &p, const ListNode<t> &q);

    template <class t>
    friend bool operator!=(const ListNode<t> &p, const ListNode<t> &q);
};

template <class T>
ListNode<T>::ListNode()
{
    this->previous = nullptr;
    this->next = nullptr;
}

template <class T>
ListNode<T>::ListNode(T data)
{
    this->data = data;
    this->previous = nullptr;
    this->next = nullptr;
}

template <class T>
ListNode<T>::ListNode(T data, ListNode<T> *previous, ListNode<T> *next)
{
    this->data = data;
    this->previous = previous;
    this->next = next;
}

template <class T>
ListNode<T>::~ListNode() {}

template <class T>
void ListNode<T>::set_data(T elem)
{
    this->data = elem;
}

template <class T>
void ListNode<T>::set_previous(ListNode<T> *previous)
{
    this->previous = previous;
}

template <class T>
void ListNode<T>::set_next(ListNode<T> *next)
{
    this->next = next;
}

template <class T>
T *ListNode<T>::get_data()
{
    return &this->data;
}

template <class T>
ListNode<T> *ListNode<T>::get_previous()
{
    return this->previous;
}

template <class T>
ListNode<T> *ListNode<T>::get_next()
{
    return this->next;
}

template <class t>
bool operator==(const ListNode<t> &p, const ListNode<t> &q)
{
    return p.next == q.next and p.previous == q.previous and p.data == q.data;
}

template <class t>
bool operator!=(const ListNode<t> &p, const ListNode<t> &q)
{
    return not(p == q);
}

#endif