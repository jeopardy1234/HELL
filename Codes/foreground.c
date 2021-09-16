#include "shell.h"

void execute_foreground(int argc, char **argv)
{
    int pid = fork();
    if(pid == 0)
    {
        if(execvp(argv[0],argv) < 0)
        {
            cprint("ERROR: ",RED);
            printf("Invalid Command!!\n");
            return;
        }    
    }
    else
        wait(NULL);
}