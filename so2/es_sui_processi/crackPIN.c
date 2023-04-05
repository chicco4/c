#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define PINLEN "5"         // lunghezza PIN come stringa per snprintf
#define CHECK "./checkPIN" // il programma da eseguire

int main(int argc)
{
    int pid, status;
    int pin;                       // il pin da provare come numero intero
    int maxbuf = atoi(PINLEN) + 1; // PINLEN+1, convertito in intero
    char pinstring[maxbuf];        // il buffer per la stringa contenente il pin
                                   // (serve un byte in più per il terminatore di stringa)

    /* il processo genitore sta in questo loop */
    for (pin = 0;; pin++)
    {
        /*
         * converte pin in pinstring mettendo un padding di zeri
         * fino a raggiungere PINLEN (5 nel nostro caso)
         */
        if (snprintf(pinstring, maxbuf, "%0" PINLEN "d", pin) >= maxbuf)
        {
            /*
             * superata la PINLEN ==> nessun pin trovato, quindi esce
             * notare che snprintf ritorna >= maxbuf quando ha troncato la stringa
             * per farla stare nel buffer (vedere la manpage)
             */
            exit(EXIT_FAILURE);
        }

        pid = fork(); // Crea il processo figlio
        if (pid < 0)
        {
            perror("errore fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            /*
             * processo figlio, esegue il check lanciando CHECK
             * con pinstring come argv[1]
             */
            execl(CHECK, CHECK, pinstring, NULL);
            /* qui non deve arrivarci mai */
            perror("Errore exec!");
            exit(EXIT_FAILURE);
        }
        /* solo il genitore continua e attende il figlio */
        if ((pid = wait(&status)) >= 0)
        {
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            {
                printf("PIN trovato: Yeah!!\n");
                exit(EXIT_SUCCESS);
            }
        }
        else
        {
            perror("errore wait");
            exit(EXIT_FAILURE);
        }
    }
}