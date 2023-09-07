#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int a = 9;

int f1(int b)
{
    {
        int a = b + 1;
    }
    return a;
}

int main()
{
    printf("%d ", f1(5));

    return 0;
}