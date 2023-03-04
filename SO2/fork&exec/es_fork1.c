#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t f1, f2, f3;

    f1 = fork();
    f2 = fork();
    f3 = fork();

    printf("%i%i%i ", (f1 > 0), (f2 > 0), (f3 > 0));
}