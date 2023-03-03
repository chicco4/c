// visualizza l'esecuzione concorrente di genitore e figlio

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid;
    int i;

    pid = fork();
    if (pid < 0)
        perror("fork error"); // stampa la descrizione dell'errore
    else if (pid == 0)
    {
        while (1)
        {
            for (i = 0; i < 10000; i++)
            {
            } // riduce il numero di printf
            printf("Figlio: pid = %d, pid del genitore = %d\n", getpid(), getppid());
        }
    }
    else
    {
        while (1)
        {
            for (i = 0; i < 10000; i++)
            {
            } // riduce il numero di printf
            printf("genitore: pid = %d, pid di mio genitore = %d\n", getpid(), getppid());
        }
    }
}
//sono eseguiti in parallelo