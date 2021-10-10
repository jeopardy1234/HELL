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
    {
        int status;
        waitpid(pid, &status, WUNTRACED);    //Shush! Wait unitl the process completes
        if(WIFSTOPPED(status))
        {
            currJob++;
            bgpr *node = malloc(sizeof(bgpr));
            node -> pid = pid;
            node -> job_number = currJob;
            strcpy(node -> process, argv[0]);
            AddNodeLL(node, BgProcesses);
            fg_to_bg = 1;
        }
    }
    fg_runnin = false;
}