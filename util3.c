#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    int a = 2;
    int *b = &a;
    int c[3] = {0, 1, 2};
    int *d = c;

    if (*(d + a) == c[a])
    {
        *b = *c;
    }
    c[*b] = *(c + *d + 1);

    return 0;
}