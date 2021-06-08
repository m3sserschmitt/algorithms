/*
 * Implementation of merge-sort algorithm.
 * O(n*lg(n)) complexity. 
*/

#include <string.h>

template <class T>
void merge(T *v, int p, int q, int r)
{
    // calculate lengths for arrays;
    int n1 = q - p + 1;
    int n2 = r - q;

    // allocate memory;
    T *L = new T[n1];
    T *R = new T[n2];

    // copy content of the two arrays into newly allocated arrays;
    for (int t = 0; t < n1; t++)
    {
        L[t] = v[p + t];
    }

    for (int u = 0; u < n2; u++)
    {
        R[u] = v[q + u + 1];
    }

    int i = 0, j = 0, k = p;

    // merge them into original array
    // and make sure to put elements into nondecreasing order;
    for (; i < n1 and j < n2; k++)
    {
        if (L[i] <= R[j])
        {
            v[k] = L[i];
            i++;
        }
        else
        {
            v[k] = R[j];
            j++;
        }
    }

    int lower = i;
    int upper = n1 - i;
    
    T *src = L;
    // copy remaining elements
    if ((i != n1) or ((lower = j) != n2 and (upper = n2 - j) and (src = R)))
    {
        for (int t = 0; t < upper; t++)
        {
            v[k + t] = src[lower + t];
        }
    }

    // release memory
    delete[] L;
    delete[] R;

    // Done!
}

template <class T>
void merge_sort(T *v, int p, int r)
{
    int q = (p + r) / 2;

    if (p < r)
    {
        // split the array into small pieces ...
        merge_sort(v, p, q);
        merge_sort(v, q + 1, r);

        // ... and then merge them, sorting the elements
        merge(v, p, q, r);
    }
}
