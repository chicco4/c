#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int *f2(int a, int b, int c)
{
    int *x = &a;
    int *y = &b;
    int *z = &c;
    *x = *y + *z;

    return &x;
}

int main()
{
    printf("%d \n", f2(1, 2, 3));

    return 0;
}
