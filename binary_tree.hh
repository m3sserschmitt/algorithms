/**
 * @file binary_tree.hh
 * @brief Declaratia pentru binary search tree
 * @version 0.1
 * @date 2021-04-23
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef BINARY_TREE_HH
#define BINARY_TREE_HH

#include "tree_node.hh"
#include <ostream>
#include <iostream>

#define PARENT(z) ((TreeNode<T> *)z->get_parent())
#define GRANDPARENT(z) ((TreeNode<T> *)(z->get_parent()->get_parent()))

template <class T>
class BinarySearchTree
{
    // printeaza nodurile arborelui in ordine crescatoare
    // pornind de la un anumit nod;
    std::ostream &in_order_tree_print(std::ostream &out, const TreeNode<T> *x, bool &c) const;

    void clear(const TreeNode<T> *x);

protected:
    // radacina arborelui;
    TreeNode<T> *root;

    // pentru compatibilitate, in cazul unui arbore simplu va fi nullptr,
    // iar pt rb-tree, pointeaza catre un tip special de nod, de culoare BLACK;
    TreeNode<T> *nil;

    // numarul de elemente;
    size_t count;

    void tree_transplant(TreeNode<T> *u, TreeNode<T> *v);

    // muta nodul v in locul nodului u
    // (deci tot subarborele cu radacina in v este "transportat" in locul nodului u)
    virtual void transplant(TreeNode<T> *u, TreeNode<T> *v);

    // returneaza radacina arborelui;
    const TreeNode<T> *get_root() const;

    // cauta nodul cu cheia k din subarborele cu radacina x;
    const TreeNode<T> *search(const TreeNode<T> *x, TreeNode<T> k) const;

    // insereaza nodul x in arbore;
    const TreeNode<T> *insert(TreeNode<T> *x);

    virtual void remove_node(const TreeNode<T> *z);

    // returneaza nodul cu cheia minima din subarborele cu radacina in nodul x;
    const TreeNode<T> *minimum(const TreeNode<T> *x) const;

    // returneaza nodul cu cheia maxima din subarborele cu radacina in nodul x;
    const TreeNode<T> *maximum(const TreeNode<T> *x) const;

    // returneaza nodul succesor al nodului x;
    const TreeNode<T> *successor(const TreeNode<T> *x) const;

    // returneaza nodul predecesor nodului x;
    const TreeNode<T> *predecessor(const TreeNode<T> *x) const;

    void kth_element(const TreeNode<T> *x, TreeNode<T> **target, size_t k, size_t &c) const;

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();

    /*
     * Metodele din cerinta proiectului;
     */

    // insereaza o noua cheie in arbore;
    virtual void insert(T x);

    // sterge o cheie din arbore;
    void remove(T x);

    // returneaza minimul din intregul arbore;
    T minimum() const;

    // returneaza maximul din intregul arbore;
    T maximum() const;

    // returneaza succesorul lui x;
    T successor(T x) const;

    // returneaza predecesorului lui x;
    T predecessor(T x) const;

    // returneaza elementul cu indexul k in ordine crescatoare;
    T kth_element(size_t k) const;

    // returneaza numarul de noduri din arbore;
    size_t size() const;

    // returneaza true daca nodul x exista in arbore, altfel false;
    bool exists(T x) const;

    // elibereaza recursiv memoria pentru toate nodurile arborelui;
    void clear();

    template <class t>
    friend std::ostream &operator<<(std::ostream &out, const BinarySearchTree<t> &tree);
};

template <class T>
BinarySearchTree<T>::BinarySearchTree()
{
    this->root = nullptr;
    this->nil = nullptr;
    this->count = 0;
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    this->clear(this->root);
}

template <class T>
const TreeNode<T> *BinarySearchTree<T>::get_root() const
{
    return this->root;
}

template <class T>
void BinarySearchTree<T>::tree_transplant(TreeNode<T> *u, TreeNode<T> *v)
{
    if (PARENT(u) == this->nil)
    {
        this->root = v;
    }
    else if (u == PARENT(u)->get_left())
    {
        PARENT(u)->set_left(v);
    }
    else
    {
        PARENT(u)->set_right(v);
    }
}

template <class T>
void BinarySearchTree<T>::transplant(TreeNode<T> *u, TreeNode<T> *v)
{
    this->tree_transplant(u, v);

    // daca v e nenul, atunci parintele lui u devine parintele lui v;
    if (v != this->nil)
    {
        v->set_parent(u->get_parent());
    }
}

template <class T>
std::ostream &BinarySearchTree<T>::in_order_tree_print(std::ostream &out, const TreeNode<T> *x, bool &c) const
{
    if (x != this->nil)
    {
        // se parcurge recursiv arborele pana la nodul
        // cu cheia cea mai mica;
        this->in_order_tree_print(out, x->get_left(), c);

        // initial c = 0, deci nu se printeaza virgula
        if (c)
        {
            out << ", ";
        } // dupa ce se printeza primul nod, c devine 1
        // deci la urmatorul apel va printa si virgula
        else
        {
            c = 1;
        }

        size_t ct = x->get_count() - 1;

        while (ct)
        {
            out << *x << ", ";
            ct--;
        }

        out << *x; /* << "[" << *x->get_left() << " " << *x->get_right() << "]"*/
        ;

        this->in_order_tree_print(out, x->get_right(), c);
    }

    return out;
}

template <class T>
const TreeNode<T> *BinarySearchTree<T>::search(const TreeNode<T> *x, TreeNode<T> k) const
{
    while (x != this->nil and k != x->get_key())
    {
        if (k < x->get_key())
        {
            x = x->get_left();
        }
        else
        {
            x = x->get_right();
        }
    }

    return x;
}

template <class T>
const TreeNode<T> *BinarySearchTree<T>::insert(TreeNode<T> *z)
{
    // pointer la radacina arborelui;
    TreeNode<T> *x = this->root;

    // auxiliar;
    TreeNode<T> *y = this->nil;

    // traverseaza arborele:
    // la fiecare pas se decide daca merge la stanga sau dreapata
    // comparand cheile, pana cand se ajunge la o frunza;
    while (x != this->nil)
    {
        y = x;
        if (z->get_key() < x->get_key())
        {
            x = (TreeNode<T> *)x->get_left();
        }
        else if (z->get_key() > x->get_key())
        {
            x = (TreeNode<T> *)x->get_right();
        }
        else
        {
            x->inc_count();
            this->count++;

            return this->nil;
        }
    }

    // seteaza parintele lui z;
    z->set_parent(y);

    // daca arborele nu a avut radacina
    if (y == this->nil)
    {
        // atunci z devine radacina;
        this->root = z;
    }
    // altfel se decide daca z este copilul drept sau stang al lui y,
    // comparand cheile;
    else if (z->get_key() < y->get_key())
    {
        y->set_left(z);
    }
    else
    {
        y->set_right(z);
    }

    this->count++;

    return z;
}

template <class T>
void BinarySearchTree<T>::remove_node(const TreeNode<T> *z)
{
    if (z->get_left() == this->nil)
    {
        this->transplant((TreeNode<T> *)z, (TreeNode<T> *)z->get_right());
    }
    else if (z->get_right() == this->nil)
    {
        this->transplant((TreeNode<T> *)z, (TreeNode<T> *)z->get_left());
    }
    else
    {
        TreeNode<T> *y = (TreeNode<T> *)this->minimum(z->get_right());

        if (y->get_parent() != z)
        {
            this->transplant(y, (TreeNode<T> *)y->get_right());
            y->set_right(z->get_right());
            ((TreeNode<T> *)y->get_right())->set_parent(y);
        }

        this->transplant((TreeNode<T> *)z, y);
        y->set_left(z->get_left());
        ((TreeNode<T> *)y->get_left())->set_parent(y);
    }
}

template <class T>
const TreeNode<T> *BinarySearchTree<T>::minimum(const TreeNode<T> *x) const
{
    if (x == this->nil)
    {
        return x;
    }

    while (x->get_left() != this->nil)
        x = x->get_left();

    return x;
}

template <class T>
const TreeNode<T> *BinarySearchTree<T>::maximum(const TreeNode<T> *x) const
{
    if (x == this->nil)
    {
        return x;
    }

    while (x->get_right() != this->nil)
        x = x->get_right();

    return x;
}

template <class T>
const TreeNode<T> *BinarySearchTree<T>::successor(const TreeNode<T> *x) const
{
    // daca copilul drept este nenul
    if (x->get_right() != this->nil)
    {
        return this->minimum(x->get_right());
    }

    const TreeNode<T> *y = x->get_parent();

    // cat timp x e copil drept se parcurge arborele spre radacina
    while (y != this->nil and x == y->get_right())
    {
        x = y;
        y = y->get_parent();
    }

    return y;
}

template <class T>
const TreeNode<T> *BinarySearchTree<T>::predecessor(const TreeNode<T> *x) const
{
    if (x->get_left() != this->nil)
    {
        return this->maximum(x->get_left());
    }

    const TreeNode<T> *y = x->get_parent();

    while (y != this->nil and x == y->get_left())
    {
        x = y;
        y = y->get_parent();
    }

    return y;
}

template <class T>
void BinarySearchTree<T>::kth_element(const TreeNode<T> *x, TreeNode<T> **target, size_t k, size_t &c) const
{
    if (x != this->nil and c < k)
    {
        this->kth_element(x->get_left(), target, k, c);

        if (c < k)
        {
            *target = (TreeNode<T> *)x;
        }

        c += x->get_count();
        this->kth_element(x->get_right(), target, k, c);
    }
}

template <class T>
void BinarySearchTree<T>::clear(const TreeNode<T> *x)
{
    // elibereaza recursiv memoria alocata pe fiecare nod;
    if (x != this->nil)
    {
        this->clear(x->get_left());
        this->clear(x->get_right());

        delete x;
    }
}

template <class T>
void BinarySearchTree<T>::insert(T n)
{
    // noul nod care va fi inserat;
    TreeNode<T> *z = new TreeNode<T>(n);

    this->insert(z);
}

template <class T>
void BinarySearchTree<T>::remove(T x)
{
    TreeNode<T> *z = (TreeNode<T> *)this->search(this->root, x);

    if (z == this->nil)
    {
        throw "Key not found";
    }

    z->dec_count();
    this->count--;

    if (not z->get_count())
    {
        this->remove_node(z);
    }
}

template <class T>
T BinarySearchTree<T>::minimum() const
{
    if (this->root == this->nil)
    {
        throw "Tree is empty";
    }

    return *this->minimum(this->root);
}

template <class T>
T BinarySearchTree<T>::maximum() const
{
    if (this->root == this->nil)
    {
        throw "Tree is empty";
    }

    return *this->maximum(this->root);
}

template <class T>
T BinarySearchTree<T>::successor(T x) const
{
    if (this->root == this->nil)
        throw "Tree is empty";

    // cauta nodul cu cheia lui x;
    const TreeNode<T> *z = this->search(this->root, x);

    // std::cout << "\nleft of " << x << " is " << *z->get_left() << "\n";
    // std::cout << "\nright of " << x << " is " << *z->get_right() << "\n";

    // eroare, daca nu s-a gasit cheia
    if (z == this->nil)
        throw "Key does not exist";

    const TreeNode<T> *x_successor = this->successor(z);

    if (x_successor == this->nil)
    {
        throw "Successor does not exist";
    }

    return *x_successor;
}

template <class T>
T BinarySearchTree<T>::predecessor(T x) const
{
    if (this->root == this->nil)
        throw "Tree is empty";

    // cauta nodul cu cheia lui x;
    const TreeNode<T> *z = this->search(this->root, x);

    if (z == this->nil)
        throw "Key does not exist";

    if (z->get_left() != this->nil)
    {
        return *this->maximum(z->get_left());
    }

    const TreeNode<T> *x_predecessor = this->predecessor(z);

    if (x_predecessor == this->nil)
    {
        throw "Predecessor does not exists";
    }

    return *x_predecessor;
}

template <class T>
size_t BinarySearchTree<T>::size() const
{
    return this->count;
}

template <class T>
bool BinarySearchTree<T>::exists(T x) const
{
    return this->search(this->root, x) != this->nil ? 1 : 0;
}

template <class T>
T BinarySearchTree<T>::kth_element(size_t k) const
{
    if (not k or k > this->count)
    {
        throw "Requested element does not exist";
    }

    size_t c = 0;
    TreeNode<T> *target = this->nil;
    this->kth_element(this->root, &target, k, c);

    return *target;
}

template <class T>
void BinarySearchTree<T>::clear()
{
    this->clear(this->root);
    this->root = this->nil;
}

template <class t>
std::ostream &operator<<(std::ostream &out, const BinarySearchTree<t> &tree)
{
    const TreeNode<t> *root = tree.root;

    // la primul apel nu se printeaza virgula
    bool c = 0;

    out << "{";
    tree.in_order_tree_print(out, root, c);
    out << "}";

    return out;
}

#endif
