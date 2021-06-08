#include "list_node.hh"

#ifndef LIST_ITERATOR_HH
#define LIST_ITERATOR_HH

template <class T>
class ListIterator
{
    ListNode<T> *node;

public:
    ListIterator(ListNode<T> *node);

    T *item();

    void next();
    void previous();

    bool in_range();

    template <class t>
    friend bool operator==(const ListIterator<t> &p, const ListIterator<t> &q);

    template <class t>
    friend bool operator!=(const ListIterator<t> &p, const ListIterator<t> &q);
};

template <class T>
ListIterator<T>::ListIterator(ListNode<T> *node)
{
    this->node = node;
}

template <class T>
T *ListIterator<T>::item()
{
    if (this->node)
    {
        return this->node->get_data();
    }

    return nullptr;
}

template <class T>
void ListIterator<T>::next()
{
    this->node and (this->node = this->node->get_next());
}

template <class T>
void ListIterator<T>::previous()
{
    this->node and (this->node = this->node->get_previous());
}

template <class T>
bool ListIterator<T>::in_range()
{
    return this->node != nullptr;
}

template <class t>
bool operator==(const ListIterator<t> &p, const ListIterator<t> &q)
{
    if (not p.node and not q.node)
    {
        return true;
    }

    return not p.node or not q.node ? false : *p.node == *q.node;
}

template <class t>
bool operator!=(const ListIterator<t> &n, const ListIterator<t> &p)
{
    return not(n == p);
}

#endif
