#include <iostream>

#include "insertion_sort.hh"
#include "merge_sort.hh"
#include "list.hh"
#include "stack.hh"
#include "queue.hh"
#include "heap_sort.hh"

#include "rb_binary_tree.hh"

using namespace std;

template <class T>
void print(T *v, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        cout << v[i] << ", ";
    }

    cout << v[n - 1] << "\n";
}

int main()
{
    int A[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int *B = new int[20];
    heap_sort(A, 10);

    print(A, 10);

    RBBinarySearchTree<int> tree;
    tree.insert(123);

    cout << tree << endl;

    return 0;
}