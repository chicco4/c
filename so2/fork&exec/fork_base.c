#include <unistd.h>
#include <stdio.h>

int main(){
    pid_t ret = fork();

    if(ret < 0){
        //ERRORE
    }
    else if(ret == 0){
        //CODICE FIGLIO
    }
    else{
        //CODICE GENITORE
    }
    return 0;
}