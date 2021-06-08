#include "list.hh"

#ifndef STACK_H
#define STACK_H

template <class T>
class Stack
{
    List<T> list;

public:
    Stack();
    Stack(const Stack<T> &s);
    // ~Stack();

    size_t get_size() const;

    void push(T item);
    T pop();

    // Stack<T> &operator=(const Stack<T> &s);

    template <class t>
    friend std::ostream &operator<<(std::ostream &out, const Stack<t> &s);
};

template <class T>
Stack<T>::Stack()
{
}

template <class T>
Stack<T>::Stack(const Stack<T> &s)
{
    this->list = s.list;
}

// template <class T>
// Stack<T>::~Stack()
// {
// }

template <class T>
size_t Stack<T>::get_size() const
{
    return this->list.get_size();
}

template <class T>
void Stack<T>::push(T item)
{
    this->list.insert_first(item);
}

template <class T>
T Stack<T>::pop()
{
    return this->list.remove_first();
}

// template <class T>
// Stack<T> &Stack<T>::operator=(const Stack<T> &s)
// {
//     if(this != &s)
//     {
//         this->list = s.list;
//     }

//     return *this;
// }

template <class t>
std::ostream &operator<<(std::ostream &out, const Stack<t> &s)
{
    out << s.list;

    return out;
}
#endif
