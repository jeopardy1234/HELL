#include "shell.h"

void execute_background(int argc, char **argv)
{
    int pid = fork();
    argv[argc-1] = NULL;
    if(pid == 0)
    {
        printf("%d\n",getpid());
        if(execvp(argv[0],argv) < 0)
        {
            printf("%d\n",getpid());
            cprint("ERROR: ",RED);
            printf("Invalid Command!!\n");
            return;
        }    
    }
}