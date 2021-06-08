#include "list.hh"

#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue
{
    List<T> list;

public:
    Queue();
    Queue(const Queue<T> &q);

    size_t get_size();

    void queue(T item);
    T dequeue();

    template <class t>
    friend std::ostream &operator<<(std::ostream &out, const Queue<t> &q);
};

template <class T>
Queue<T>::Queue() {}

template <class T>
Queue<T>::Queue(const Queue<T> &q)
{
    this->list = q.list;
}

template <class T>
size_t Queue<T>::get_size()
{
    return this->list.get_size();
}

template <class T>
void Queue<T>::queue(T item)
{
    this->list.insert_last(item);
}

template <class T>
T Queue<T>::dequeue()
{
    return this->list.remove_first();
}

template <class t>
std::ostream &operator<<(std::ostream &out, const Queue<t> &q)
{
    out << q.list;

    return out;
}

#endif