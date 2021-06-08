#ifndef RB_NODE_HH
#define RB_NODE_HH

#include "tree_node.hh"

// colorile posibile pentru un nod
enum NodeColor
{
    RED = 0,
    BLACK = 1
};

template <class T>
class RedBlackTreeNode : public TreeNode<T>
{
    // culoarea nodului;
    NodeColor color;

public:
    RedBlackTreeNode();
    RedBlackTreeNode(T x);
    RedBlackTreeNode(T x, NodeColor color);
    RedBlackTreeNode(const RedBlackTreeNode<T> &node);
    RedBlackTreeNode(const TreeNode<T> &node);

    // returneaza nodul parinte;
    const RedBlackTreeNode<T> *get_parent() const;

    // returneaza copilul stang;
    const RedBlackTreeNode<T> *get_left() const;

    // returneaza copilul drept;
    const RedBlackTreeNode<T> *get_right() const;

    // returneaza culoarea nodului;
    NodeColor get_color() const;

    // seteaza culoarea nodului;
    void set_color(NodeColor color);

    RedBlackTreeNode<T> &operator=(const RedBlackTreeNode<T> &node);
    RedBlackTreeNode<T> &operator=(T x);
};

template <class T>
const RedBlackTreeNode<T> *RedBlackTreeNode<T>::get_parent() const
{
    return (RedBlackTreeNode<T> *)this->p;
}

template <class T>
const RedBlackTreeNode<T> *RedBlackTreeNode<T>::get_left() const
{
    return (RedBlackTreeNode<T> *)this->left;
}

template <class T>
const RedBlackTreeNode<T> *RedBlackTreeNode<T>::get_right() const
{
    return (RedBlackTreeNode<T> *)this->right;
}

template <class T>
RedBlackTreeNode<T>::RedBlackTreeNode() : TreeNode<T>()
{
    this->color = RED;
}

template <class T>
RedBlackTreeNode<T>::RedBlackTreeNode(T x) : TreeNode<T>(x)
{
    this->color = RED;
}

template <class T>
RedBlackTreeNode<T>::RedBlackTreeNode(T x, NodeColor color) : TreeNode<T>(x)
{
    this->color = color;
}

template <class T>
RedBlackTreeNode<T>::RedBlackTreeNode(const RedBlackTreeNode<T> &node) : TreeNode<T>(node)
{
    this->color = node.color;
}

template <class T>
RedBlackTreeNode<T>::RedBlackTreeNode(const TreeNode<T> &node) : TreeNode<T>(node)
{
    this->color = RED;
}

template <class T>
NodeColor RedBlackTreeNode<T>::get_color() const
{
    return this->color;
}

template <class T>
void RedBlackTreeNode<T>::set_color(NodeColor color)
{
    this->color = color;
}

template <class T>
RedBlackTreeNode<T> &RedBlackTreeNode<T>::operator=(const RedBlackTreeNode<T> &node)
{
    TreeNode<T>::operator=(node);
    if (this != &node)
    {
        this->color = node.color;
    }

    return *this;
}

template <class T>
RedBlackTreeNode<T> &RedBlackTreeNode<T>::operator=(T x)
{
    TreeNode<T>::operator=(x);
    this->color = RED;

    return *this;
}

#endif
