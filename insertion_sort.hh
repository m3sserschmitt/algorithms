/*
 * Implementation of insertion sort algorithm.
 * O(n^2) Complexity.
 */


template <class T>
void insertion_sort(T *v, int n)
{
    int j; 
    T key;

    for (int i = 1; i < n; i++)
    {
        key = v[i];
        j = i - 1;

        while (j >= 0 and v[j] > key)
        {
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = key;
    }
}
