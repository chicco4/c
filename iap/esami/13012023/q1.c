#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int x = 3;

int f1(int w)
{
    printf("(%d)", w);
    if (w % 2 == 0)
    {
        printf("!");
        return x * 5;
    }
    else
    {
        printf("?");
        int x = w * 3;
    }
    printf("[%d]", x);
    return x;
}

int main()
{
    printf("%d ", f1(x++));
    printf("%d ", f1(x++));

    return 0;
}
