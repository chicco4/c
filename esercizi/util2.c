#include <stdio.h>
#include <stdlib.h>

int x = 1;
int g(int y)
{
    return ++x + y;
}
int f(int x)
{
    int z = x;

    {
        int x = g(z);
        return x + 1;
    }
}

int main(void)
{

    printf("%d\n", f(0));

    return 0;
}