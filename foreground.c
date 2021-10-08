#include "shell.h"

void execute_foreground(int argc, char **argv)
{
    int pid = fork();                   //Create a child process
    fg_runnin = 1;
    if(pid == 0)
    {
        if(execvp(argv[0],argv) < 0)    //Invalid command
        {
            cprint("ERROR: ",RED);
            printf("Invalid Command!!\n");
            exit(0);
        }    
    }
    else
        wait(NULL);                     //Shush! Wait unitl the process completes
    fg_runnin = false;
}