
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    system("clear");

    int a_length = 10;

    int *a = (int *)malloc(a_length * sizeof(int));

    // int *a = (int *)calloc(a_length, sizeof(int));

    for (size_t i = 0; i < a_length; i++)
    {
        a[i] = i;
    }

    for (size_t i = 0; i < a_length; i++)
    {
        printf("%d ", a[i]);
    }

    // for (size_t i = 0; i < a_length; i++)
    // {
    //     printf("%d ", *(a+1));
    // }

    printf("\n");

    int *b = (int *)realloc(a, (a_length * 2) * sizeof(int));

    for (size_t i = 0; i < (a_length * 2); i++)
    {
        printf("%d ", b[i]);
    }

    return 0;
}