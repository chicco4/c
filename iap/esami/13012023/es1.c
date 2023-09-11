#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int count_twice(int *A, size_t A_len, int *B, size_t B_len)
{
    return 0;
}

int main()
{

    int A[] = {2, 4, 6, 8, 10};
    int B[] = {1, 2, 3, 4, 5};
    printf("%d \n", count_twice(A, 5, B, 5));

    int C[] = {10, 20, 30, 40};
    int D[] = {5, 10, 20, 20};
    printf("%d \n", count_twice(C, 4, D, 4));

    return 0;
}
