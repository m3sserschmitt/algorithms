#ifndef RB_BINARY_TREE_HH
#define RB_BINARY_TREE_HH

#include "binary_tree.hh"
#include "rb_tree_node.hh"

#define RB_PARENT(z) ((RedBlackTreeNode<T> *)z->get_parent())
#define RB_GRANDPARENT(z) ((RedBlackTreeNode<T> *)(z->get_parent()->get_parent()))

template <class T>
class RBBinarySearchTree : public BinarySearchTree<T>
{
    // rotatie spre stanga in jurul nodului x;
    void left_rotate(TreeNode<T> *x);

    // rotatie la dreapta in jurul nodului x;
    void right_rotate(TreeNode<T> *x);

    // restabileste culorile in arbore dupa inserarea unui nou nod;
    void insert_fixup(RedBlackTreeNode<T> *z);

    //restabileste culorile in arbore dupa stergerea unui nod
    void remove_fixup(RedBlackTreeNode<T> *z);

protected:
    void remove_node(const TreeNode<T> *z);

    void transplant(TreeNode<T> *u, TreeNode<T> *v);

public:
    RBBinarySearchTree();
    ~RBBinarySearchTree();

    void insert(T x);
    // void remove(T x);
};

template <class T>
RBBinarySearchTree<T>::RBBinarySearchTree() : BinarySearchTree<T>()
{
    this->nil = new RedBlackTreeNode<T>(0, BLACK);
    this->root = this->nil;
}

template <class T>
RBBinarySearchTree<T>::~RBBinarySearchTree()
{
    delete this->nil;
}

template <class T>
void RBBinarySearchTree<T>::left_rotate(TreeNode<T> *x)
{
    // se presupune ca dreapta lui x este nenula;
    TreeNode<T> *y = (TreeNode<T> *)x->get_right();

    // dreapta lui x devine stanga lui y;
    x->set_right(y->get_left());

    // daca stanga lui y este nenula
    if (y->get_left() != this->nil)
    {
        // atunci stanga lui y primeste ca parinte pe x;
        TreeNode<T> *y_left = (TreeNode<T> *)y->get_left();
        y_left->set_parent(x);
    }

    // parintele lui x devine acum parintele lui y;
    y->set_parent(x->get_parent());

    TreeNode<T> *x_parent = (TreeNode<T> *)x->get_parent();

    // daca parintele lui x este nul (i.e. x este radacina)
    if (x_parent == this->nil)
    {
        // atunci y devine radacina
        this->root = y;
    }
    // daca x a fost copil stang
    else if (x == x_parent->get_left())
    {
        // atunci y devine si el copil stang;
        x_parent->set_left(y);
    }
    else // altfel devine copil drept;
    {
        x_parent->set_right(y);
    }

    // x este acum stanga lui y;
    y->set_left(x);

    // dupa care y devine parintele lui x;
    x->set_parent(y);
}

template <class T>
void RBBinarySearchTree<T>::right_rotate(TreeNode<T> *x)
{
    // codul este perfect simetric cu cazul "left_rotate"
    // doar se interschimba "left" cu "right";

    TreeNode<T> *y = (TreeNode<T> *)x->get_left();
    x->set_left(y->get_right());

    if (y->get_right() != this->nil)
    {
        TreeNode<T> *y_right = (TreeNode<T> *)y->get_right();
        y_right->set_parent(x);
    }

    y->set_parent(x->get_parent());

    TreeNode<T> *x_parent = (TreeNode<T> *)x->get_parent();

    if (x_parent == this->nil)
    {
        this->root = y;
    }
    else if (x == x_parent->get_left())
    {
        x_parent->set_left(y);
    }
    else
    {
        x_parent->set_right(y);
    }

    y->set_right(x);
    x->set_parent(y);
}

template <class T>
void RBBinarySearchTree<T>::insert_fixup(RedBlackTreeNode<T> *z)
{
    RedBlackTreeNode<T> *y;

    while (RB_PARENT(z)->get_color() == RED)
    {
        if (z->get_parent() == RB_GRANDPARENT(z)->get_left())
        {
            y = (RedBlackTreeNode<T> *)z->get_parent()->get_parent()->get_right();

            if (y->get_color() == RED)
            {
                RB_PARENT(z)->set_color(BLACK);
                y->set_color(BLACK);
                RB_GRANDPARENT(z)->set_color(RED);
                z = RB_GRANDPARENT(z);
            }
            else
            {
                if (z == z->get_parent()->get_right())
                {
                    z = RB_PARENT(z);
                    this->left_rotate(z);
                }

                RB_PARENT(z)->set_color(BLACK);
                RB_GRANDPARENT(z)->set_color(RED);
                this->right_rotate(RB_GRANDPARENT(z));
            }
        }
        else
        {
            y = (RedBlackTreeNode<T> *)z->get_parent()->get_parent()->get_left();

            if (y->get_color() == RED)
            {
                RB_PARENT(z)->set_color(BLACK);
                y->set_color(BLACK);
                RB_GRANDPARENT(z)->set_color(RED);
                z = RB_GRANDPARENT(z);
            }
            else
            {
                if (z == z->get_parent()->get_left())
                {
                    z = RB_PARENT(z);
                    this->right_rotate(z);
                }

                RB_PARENT(z)->set_color(BLACK);
                RB_GRANDPARENT(z)->set_color(RED);
                this->left_rotate(RB_GRANDPARENT(z));
            }
        }
    }

    ((RedBlackTreeNode<T> *)this->root)->set_color(BLACK);
}

template <class T>
void RBBinarySearchTree<T>::transplant(TreeNode<T> *u, TreeNode<T> *v)
{
    this->tree_transplant(u, v);

    v->set_parent(u->get_parent());
}

template <class T>
void RBBinarySearchTree<T>::insert(T x)
{
    // copiaza cheia lui n intr-un RedBlackTreeNode;
    RedBlackTreeNode<T> *z = new RedBlackTreeNode<T>(x);

    // inserarea propriu-zisa nu tine cont de culoare
    // deci se poate apela metoda insert ca intr-un arbore simplu;
    if (BinarySearchTree<T>::insert(z) != this->nil)
    {
        // seteaza copiii lui z la nil;
        z->set_left(this->nil);
        z->set_right(this->nil);

        // insert_fixup este specifica unui RedBlackSearchTree
        // si restabileste regulile unui RB-Tree;
        this->insert_fixup(z);
    }
}

template <class T>
void RBBinarySearchTree<T>::remove_node(const TreeNode<T> *z)
{
    // copiaza cheia lui n intr-un RedBlackTreeNode;
    RedBlackTreeNode<T> *y;
    RedBlackTreeNode<T> *x;

    y = (RedBlackTreeNode<T> *)z;
    NodeColor y_original_color = y->get_color();

    if (z->get_left() == this->nil)
    {
        x = (RedBlackTreeNode<T> *)z->get_right();
        this->transplant((TreeNode<T> *)z, (TreeNode<T> *)z->get_right());
    }
    else if (z->get_right() == this->nil)
    {
        x = (RedBlackTreeNode<T> *)z->get_left();
        this->transplant((TreeNode<T> *)z, (TreeNode<T> *)z->get_left());
    }
    else
    {
        y = (RedBlackTreeNode<T> *)this->minimum(z->get_right()); // <- treb apelata functia din binary_tree
        y_original_color = y->get_color();
        x = (RedBlackTreeNode<T> *)y->get_right();

        if (y->get_parent() == z)
        {
            x->set_parent(y);
        }
        else
        {
            this->transplant(y, (TreeNode<T> *)y->get_right());
            y->set_right(z->get_right());
            ((TreeNode<T> *)y->get_right())->set_parent(y);
        }

        this->transplant((TreeNode<T> *)z, y);
        y->set_left(z->get_left());
        ((TreeNode<T> *)y->get_left())->set_parent(y);
        y->set_color(((RedBlackTreeNode<T> *)z)->get_color());
    }

    delete z;

    if (y_original_color == BLACK)
    {
        remove_fixup(x);
    }
}

template <class T>
void RBBinarySearchTree<T>::remove_fixup(RedBlackTreeNode<T> *x)
{
    RedBlackTreeNode<T> *w;

    while (x != this->root && x->get_color() == BLACK)
    {
        if (x == x->get_parent()->get_left())
        {
            w = (RedBlackTreeNode<T> *)x->get_parent()->get_right();
            if (w->get_color() == RED)
            {
                w->set_color(BLACK);
                RB_PARENT(x)->set_color(RED);
                this->left_rotate(PARENT(x)); // <------ aici
                w = (RedBlackTreeNode<T> *)x->get_parent()->get_right();
            }

            if (w->get_left()->get_color() == BLACK && w->get_right()->get_color() == BLACK)
            {
                w->set_color(RED);
                x = RB_PARENT(x);
            }
            else
            {
                if (w->get_right()->get_color() == BLACK)
                {
                    ((RedBlackTreeNode<T> *)w->get_left())->set_color(BLACK);
                    w->set_color(RED);
                    this->right_rotate(w); // <------- si aici
                    w = (RedBlackTreeNode<T> *)x->get_parent()->get_right();
                }

                w->set_color(x->get_parent()->get_color());
                RB_PARENT(x)->set_color(BLACK);
                ((RedBlackTreeNode<T> *)w->get_right())->set_color(BLACK);
                this->left_rotate(RB_PARENT(x)); // <---------- si aici
                x = (RedBlackTreeNode<T> *)this->root;
            }
        }
        else
        {
            w = (RedBlackTreeNode<T> *)x->get_parent()->get_left();
            if (w->get_color() == RED)
            {
                w->set_color(BLACK);
                RB_PARENT(x)->set_color(RED);
                this->right_rotate(PARENT(x));
                w = (RedBlackTreeNode<T> *)x->get_parent()->get_left();
            }

            if (w->get_right()->get_color() == BLACK && w->get_left()->get_color() == BLACK)
            {
                w->set_color(RED);
                x = RB_PARENT(x);
            }
            else
            {
                if (w->get_left()->get_color() == BLACK)
                {
                    ((RedBlackTreeNode<T> *)w->get_right())->set_color(BLACK);
                    w->set_color(RED);
                    this->left_rotate(w); // aiici
                    w = (RedBlackTreeNode<T> *)x->get_parent()->get_left();
                }

                w->set_color(x->get_parent()->get_color());
                RB_PARENT(x)->set_color(BLACK);
                ((RedBlackTreeNode<T> *)w->get_left())->set_color(BLACK);
                this->right_rotate(RB_PARENT(x)); // aici
                x = (RedBlackTreeNode<T> *)this->root;
            }
        }
    }

    x->set_color(BLACK);
}

#endif
