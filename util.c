#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    system("clear");

    int a;  // Declares a variable
    int *b; // Declares a pointer
    //int &c; // Not possible

    a = 10;
    b = &a;  // b gets the address of a
    *b = 20; // a now has the value 20


    printf("a -> %d\n", a);
    printf("b -> %d\n", b);
    //printf("c -> %d\n", c);

    int x = 10;
    int y = 10;

    printf("x -> %d\n", x++);
    printf("x -> %d\n", x);

    printf("y -> %d\n", ++y);
    printf("y -> %d\n", y);

    return 0;
}