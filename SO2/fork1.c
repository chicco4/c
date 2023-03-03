#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t pid;

    printf("prima della fork, pid = %d, pid del genitore = %d\n", getpid(), getppid());

    if ((pid = fork()) < 0)
    {
        // ERRORE
        printf("errore duante la fork");
    }
    else if (pid == 0)
    {
        // FIGLIO
        printf("[figlio] valore restituito dalla fork: %d\n", pid);
        printf("[figlio] pid = %d, pid del genitore = %d\n", getpid(), getppid());
    }
    else
    {
        // GENITORE
        printf("[genitore] valore restituito dalla fork: %d\n", pid);
        printf("[genitore] pid = %d, pid del mio genitore = %d\n", getpid(), getppid());
        printf("[genitore] mio figlio ha pid = %d\n", pid);
    }

    return 0;
}