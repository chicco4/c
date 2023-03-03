#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    pid_t ret = fork();

    

    system("./checkPIN 01234");
    
}
