#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        // ERRORE
        printf("errore duante la fork");
    }
    else if (pid == 0)
    {
        // FIGLIO
        sleep(5);
        printf("[figlio] pid = %d, pid del genitore = %d\n", getpid(), getppid());
    }
    else
    {
        // GENITORE
        printf("[genitore] pid = %d, pid del mio genitore = %d\n", getpid(), getppid());
        printf("[genitore] mio figlio ha pid = %d\n", pid);
    }

    return 0;
}