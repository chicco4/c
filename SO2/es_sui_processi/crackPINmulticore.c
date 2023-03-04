#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define PINLEN "5"         // lunghezza PIN come stringa per snprintf
#define CHECK "./checkPIN" // il programma da eseguire
#define NCORES 8           // Numero di core

/*
 * Funzione che fa il check dello status ed esce quando
 * la exit ha ritornato zero.
 * Viene riutilizzata in diversi punti del main
 *
 * https://secgroup.dais.unive.it/teaching/laboratorio-sistemi-operativi/esercitazione-su-gestione-dei-processi/task-5-extra-brute-forcing-multi-core/
 */
void check(int status)
{
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
    {
        printf("PIN trovato: Yeah!!\n");
        exit(EXIT_SUCCESS);
    }
}

int main(int argc)
{
    int pid, status;
    int pin;                       // il pin da provare come numero intero
    int maxbuf = atoi(PINLEN) + 1; // PINLEN+1, convertito in intero
    char pinstring[maxbuf];        // il buffer per la stringa contenente il pin
                                   // (il byte in più è per il terminatore di stringa)
    int activecores = 1;           // numero di core attivi

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
        /*
         * solo il genitore continua: ha fatto la fork
         * incrementa i numero di core occupati
         */
        activecores++;
        /*
         * Se i core sono pieni attende un figlio:
         * a regime appena uno finisce ne lancia un altro
         */
        if (activecores == NCORES)
        {
            if ((pid = wait(&status)) >= 0)
            {
                activecores--; // il figlio ha liberato un core
                check(status); // controlla se ha trovato il PIN
            }
        }
    }
    /* attende eventuali figli ancora in esecuzione */
    while ((pid = wait(&status)) >= 0)
    {
        check(status);
    }
}