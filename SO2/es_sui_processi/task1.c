#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

/*https://secgroup.dais.unive.it/teaching/laboratorio-sistemi-operativi/esercitazione-su-gestione-dei-processi/task-1-il-programma-da-craccare/*/

int main()
{
    pid_t ret = fork();

    system("./checkPIN 01234");
}
