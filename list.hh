#include "list_iterator.hh"

#include <stdexcept>
#include <ostream>

#ifndef LIST_H
#define LIST_H

template <class T>
class List
{
    // pointer to first element;
    ListNode<T> *first;

    // pointer to last element;
    ListNode<T> *last;

    size_t len;

public:
    List();
    List(const List<T> &l);
    ~List();

    size_t get_size() const;

    // insert last;
    void insert_last(T item);

    // insert at begining of list;
    void insert_first(T item);

    // remove lat element;
    T remove_last();

    // remove first element;
    T remove_first();

    // get iterator pointing at first element;
    ListIterator<T> begin() const;

    // get iterator pointing at last element;
    ListIterator<T> end() const;

    List<T> &operator=(const List<T> &l);

    template <class t>
    friend std::ostream &operator<<(std::ostream &out, const List<t> &l);
};

template <class T>
List<T>::List()
{
    this->first = nullptr;
    this->last = nullptr;

    this->len = 0;
}

template <class T>
List<T>::List(const List<T> &l)
{
    this->first = nullptr;
    this->last = nullptr;
    this->len = 0;

    if (l.len)
    {
        // pointer to first node;
        ListNode<T> *node = l.first;

        // first and last point to same node at begining;
        this->first = new ListNode<T>(*node->get_data());
        this->last = this->first;

        // iterate over list, allocate memory and copy data;
        while ((node = node->get_next()))
        {
            ListNode<T> *new_node = new ListNode<T>(*node->get_data());

            this->last->set_next(new_node);
            new_node->set_previous(this->last);

            this->last = new_node;
        }

        // set list size;
        this->len = l.len;
    }
}

template <class T>
List<T>::~List()
{
    while (this->first)
    {
        delete this->first;

        this->first = this->first->get_next();
    }
}

template <class T>
size_t List<T>::get_size() const
{
    return this->len;
}

template <class T>
void List<T>::insert_last(T item)
{
    ListNode<T> *new_node = new ListNode<T>(item, this->last, nullptr);

    if (not this->len)
    {
        this->first = new_node;
    }
    else
    {
        this->last->set_next(new_node);
    }

    this->last = new_node;
    this->len++;
}

template <class T>
void List<T>::insert_first(T item)
{
    ListNode<T> *new_node = new ListNode<T>(item, nullptr, this->first);

    if (not this->len)
    {
        this->last = new_node;
    }
    else
    {
        this->first->set_previous(new_node);
    }

    this->first = new_node;
    this->len++;
}

template <class T>
T List<T>::remove_first()
{
    if (this->len)
    {
        ListNode<T> *second = this->first->get_next();
        T item = *this->first->get_data();

        delete this->first;

        this->first = second;

        if (this->first)
        {
            this->first->set_previous(nullptr);
        }

        this->len--;

        return item;
    }

    throw std::runtime_error("list empty");
}

template <class T>
T List<T>::remove_last()
{
    if (this->last)
    {
        ListNode<T> *previous = this->last->get_previous();
        T item = *this->last->get_data();

        delete this->last;

        this->last = previous;

        if (this->last)
        {
            this->last->set_next(nullptr);
        }

        this->len--;

        return item;
    }

    throw std::runtime_error("list empty");
}

template <class T>
ListIterator<T> List<T>::begin() const
{
    return ListIterator<T>(this->first);
}

template <class T>
ListIterator<T> List<T>::end() const
{
    return ListIterator<T>(this->last);
}

template <class T>
List<T> &List<T>::operator=(const List<T> &l)
{
    if (this != &l)
    {
        // iterate over list and delete old data;
        while (this->first)
        {
            delete this->first;

            this->first = this->first->get_next();
        }

        this->first = nullptr;
        this->last = nullptr;
        this->len = 0;

        if (l.len)
        {
            // pointer to first node of new list;
            ListNode<T> *node = l.first;

            // first and last point to same node at begining;
            this->first = new ListNode<T>(*node->get_data());
            this->last = this->first;

            // iterate over list, allocate memory and copy data;
            while ((node = node->get_next()))
            {
                ListNode<T> *new_node = new ListNode<T>(*node->get_data());

                this->last->set_next(new_node);
                new_node->set_previous(this->last);

                this->last = new_node;
            }

            // set list size;
            this->len = l.len;
        }
    }

    return *this;
}

template <class t>
std::ostream &operator<<(std::ostream &out, const List<t> &l)
{
    ListNode<t> *node = l.first;

    out << "{";
    while (node)
    {
        node->get_data() and out << *node->get_data();
        (node = node->get_next()) and out << ", ";
    }
    out << "}";

    return out;
}
#endif
