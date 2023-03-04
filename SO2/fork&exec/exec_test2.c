#include <unistd.h>
#include <stdio.h>

int main()
{

    printf("sono processo con pid: %d\n", getpid());
    printf("provo ad eseguire un codice esterno!\n");

    execl("./eseguibile", NULL);

    printf("sostituzione di codice fallita!");
    // se la exec va a buon fine questa printf non viene eseguita

    return 0;
}