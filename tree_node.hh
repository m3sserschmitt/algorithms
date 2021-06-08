/**
 * @file node.h
 * @brief Clasa TreeNode memoreaza datele(parintele, copiii si cheia) unui nod din arbore;
 * @version 0.1
 * @date 2021-04-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef NODE_HH
#define NODE_HH

#include <ostream>
#include <istream>

template <class T>
class TreeNode
{
protected:
    TreeNode *p;     // parintele nodului;
    TreeNode *left;  // copilul stang;
    TreeNode *right; // copilul drept;
    size_t count;    // de cate ori se repeta cheia in multime;
    T key;           // cheia nodului;

public:
    TreeNode();
    TreeNode(T x);
    TreeNode(const TreeNode &node);
    virtual ~TreeNode();

    void inc_count();
    void dec_count();
    size_t get_count() const;

    // returneaza nodul parinte;
    const TreeNode<T> *get_parent() const;

    // returneaza copilul stang;
    const TreeNode<T> *get_left() const;

    // returneaza copilul drept;
    const TreeNode<T> *get_right() const;

    // seteaza parintele;
    void set_parent(const TreeNode<T> *node);

    // seteaza copilul stang;
    void set_left(const TreeNode<T> *node);

    // seteaza copilul drept;
    void set_right(const TreeNode<T> *node);

    // returneaza cheia nodului;
    T get_key() const;

    // seteaza cheia nodului;
    void set_key(T key);

    TreeNode<T> &operator=(const TreeNode<T> &node);
    TreeNode<T> &operator=(T key);

    operator T() const;

    template <class t>
    friend std::ostream &operator<<(std::ostream &out, const TreeNode<t> &node);

    template <class t>
    friend std::istream &operator>>(std::istream &in, TreeNode<t> &node);
};

template <class T>
TreeNode<T>::TreeNode()
{
    this->p = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->count = 1;
}

template <class T>
TreeNode<T>::TreeNode(T key)
{
    this->p = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->count = 1;
    this->key = key;
}

template <class T>
TreeNode<T>::TreeNode(const TreeNode<T> &node)
{
    this->p = node.p;
    this->left = node.left;
    this->right = node.right;
    this->key = node.key;
    this->count = node.count;
}

template <class T>
TreeNode<T>::~TreeNode() {}

template <class T>
void TreeNode<T>::inc_count()
{
    this->count++;
}

template <class T>
void TreeNode<T>::dec_count()
{
    this->count--;
}

template <class T>
size_t TreeNode<T>::get_count() const
{
    return this->count;
}

template <class T>
const TreeNode<T> *TreeNode<T>::get_parent() const
{
    return this->p;
}

template <class T>
const TreeNode<T> *TreeNode<T>::get_left() const
{
    return this->left;
}

template <class T>
const TreeNode<T> *TreeNode<T>::get_right() const
{
    return this->right;
}

template <class T>
void TreeNode<T>::set_parent(const TreeNode<T> *node)
{
    this->p = (TreeNode *)node;
}

template <class T>
void TreeNode<T>::set_left(const TreeNode<T> *node)
{
    this->left = (TreeNode *)node;
}

template <class T>
void TreeNode<T>::set_right(const TreeNode<T> *node)
{
    this->right = (TreeNode *)node;
}

template <class T>
T TreeNode<T>::get_key() const
{
    return this->key;
}

template <class T>
void TreeNode<T>::set_key(T x)
{
    this->key = key;
}

template <class T>
TreeNode<T>::operator T() const
{
    return this->key;
}

template <class T>
TreeNode<T> &TreeNode<T>::operator=(const TreeNode<T> &node)
{
    if (this != &node)
    {
        this->p = node.p;
        this->left = node.left;
        this->right = node.right;
        this->key = node.key;
    }

    return *this;
}

template <class T>
TreeNode<T> &TreeNode<T>::operator=(T x)
{
    this->p = nullptr;
    this->left = nullptr;
    this->right = nullptr;
    this->key = x;

    return *this;
}

template <class t>
std::ostream &operator<<(std::ostream &out, const TreeNode<t> &node)
{
    out << node.get_key();

    return out;
}

template <class t>
std::istream &operator>>(std::istream &in, TreeNode<t> &node)
{
    int x;
    in >> x;

    node.set_key(x);

    return in;
}

#endif
