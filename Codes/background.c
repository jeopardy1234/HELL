#include "shell.h"

void execute_background(int argc, char **argv)
{
    int pid = fork();
    if(pid == 0)
    {
        if(execvp(argv[0],argv) < 0)
        {
            printf("%d\n",getpid());
            cprint("ERROR: ",RED);
            printf("Invalid Command!!\n");
            return;
        }    
    }
    printf("%d",pid);
}