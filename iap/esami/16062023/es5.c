/* Scrivere una funzione ricorsiva che dati due array di interi non vuoti conteggi il numero di volte che il primo
array appare nel secondo senza sovrapposizioni. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_prefixarray(int *a, int a_size, int *b, int b_size)
{
    if (a_size > b_size)
        return false;
    for (int i = 0; i < a_size; i++)
        if (a[i] != b[i])
            return false;
    return true;
}

int count_array(int *a, int a_size, int *b, int b_size)
{
    if (b_size <= 0)
        return 0;
    if (is_prefixarray(a, a_size, b, b_size))
        return 1 + count_array(a, a_size, b + a_size, b_size - a_size);
    else
        return count_array(a, a_size, b + 1, b_size - 1);
}

int main()
{
    int v1[] = {7, 3, 7};
    int v2[] = {7, 3, 7, 3, 7, 7, 3, 7, 0};
    printf("%d \n", count_array(v1, 3, v2, 9)); /* 2 a partire dalle posizioni 0 e 5 di v2 */

    return 0;
}
