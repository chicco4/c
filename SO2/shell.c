#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    pid_t esito = 1, i;
    char comando[128], *argv[128], *pch;
    while (1)
    {
        printf("myshell# "); // il prompt dei comandi
        // il codice che segue separa gli argomenti e
        // salva i puntatori in argv[]
        fgets(comando, 128, stdin);   // legge l'input dell'utente
        pch = strtok(comando, " \n"); // "parsa" il primo argomento
        for (i = 0; pch != NULL && i < 127; i++)
        {
            argv[i] = pch;
            pch = strtok(NULL, " \n"); // "parsa" gli argomenti successivi
        }
        argv[i] = NULL; // termina l'array argv con NULL
        if (argv[0] != 0)
        {                   // comando vuoto, ignora
            esito = fork(); // crea un processo figlio
            if (esito < 0)
                perror("fallimento fork");
            else if (esito == 0)
            {
                execvp(argv[0], argv); // esegue il comando!
                perror("Errore esecuzione");
                exit(EXIT_FAILURE);
            }
        }
    } // il processo genitore (shell) torna a leggere un altro comando
}

/**
 * Non attende la terminazione del processo figlio: è come avere un & implicito.
 * Lo si nota anche dal prompt myshell# immediatamente prima della lista dei file generata da ls:
 * la shell chiede subito il comando successivo senza aspettare il risultato di quello precedente.
 */