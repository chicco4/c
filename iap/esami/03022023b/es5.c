#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// restituisce tutti i sotto-insiemi che sommati fanno n
int count_subsets(int *A, int A_size, int n)
{
    if (A_size == 0) // caso base: non ci sono altri elementi in A
        return 0;

    return (A[0] == n) +                                // con A[0] raggiungo il target n
           count_subsets(A + 1, A_size - 1, n - A[0]) + // sotto-insiemi che includono A[0]
           count_subsets(A + 1, A_size - 1, n);         // sotto-insiemi che non includono A[0]
}

int main()
{

    int v[] = {1, 2, 3, 0, 6, 7};
    printf("%d \n", count_subsets(v, 6, 6));

    /* le combinazioni possibili sono:
    (6), (6, 0), (1, 2, 3), (1, 2, 3, 0) */

    return 0;
}
