/**
 * @file heap_sort.hh
 * @brief Implementation of heapsort algorithm: O(n*lg(n)) complexity.
 * @version 0.1
 * @date 2021-03-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef HEAP_SORT_H
#define HEAP_SORT_H

/**
 * @brief Return right node index.
 * 
 */
#define RIGHT(n) 2 * (n + 1)

/**
 * @brief Return left node index.
 * 
 */
#define LEFT(n) 2 * n + 1

/**
 * @brief Heap data structure.
 * 
 * @tparam T Data type.
 */
template <class T>
struct heap_t
{

    T *v;          //!< Array containing tree data.
    int heap_size; //!< Heap size.
};

/**
 * @brief Transfrom provided heap in order to obey max-heap rule
 * 
 * @tparam T 
 * @param h Heap data structure.
 * @param i Tree index to begin with.
 */
template <class T>
void max_heapify(heap_t<T> *h, int i)
{
    // left and right indexes;
    int l = LEFT(i);
    int r = RIGHT(i);

    // suppose current node is the largest;
    int largest = i;

    // compare with left and right and update largest accordingly;
    l<h->heap_size and h->v[l]> h->v[i] and (largest = l);
    r<h->heap_size and h->v[r]> h->v[largest] and (largest = r);

    // if current node is not the largest
    if (largest != i)
    {
        // then interchange them;
        int aux = h->v[largest];
        h->v[largest] = h->v[i];
        h->v[i] = aux;

        // run again on the largest node;
        max_heapify(h, largest);
    }
}

/**
 * @brief Build a max-heap structure from an unordered array.
 * 
 * @tparam T Data type.
 * @param h Heap data to be build.
 */
template <class T>
void build_max_heap(heap_t<T> *h)
{
    // since all nodes n / 2, n / 2 + 1, ..., n are all leaves (trivial max-heaps),
    // we run max_heapify over remaining nodes;
    for (int i = h->heap_size / 2 - 1; i >= 0; i--)
    {
        max_heapify(h, i);
    }
}

/**
 * @brief Sort an array using heapsort algorithm
 * 
 * @tparam T Data type.
 * @param v Array to be sorted
 * @param n Number of elemets.
 */
template <class T>
void heap_sort(T *v, int n)
{
    heap_t<T> *h = new heap_t<T>;

    // setup data and heap size;
    h->v = v;
    h->heap_size = n;

    int aux;

    // build max-heap;
    build_max_heap(h);

    while (h->heap_size > 1)
    {
        // decrement heap size
        h->heap_size--;

        // since h->v[0] contains the largest value
        // move it onto the last position in the array
        aux = h->v[h->heap_size];
        h->v[h->heap_size] = h->v[0];
        h->v[0] = aux;

        // reestablish max-heap rule, and repeat the process
        max_heapify(h, 0);
    }

    delete h;
}

#endif
