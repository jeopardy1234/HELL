#include "shell.h"

void execute_background(int argc, char **argv)
{
    int pid = fork();       //Create a child process
    argv[argc-1] = NULL;    //else execvp wont work sometimes
    if(pid == 0)
    {
        printf("%d\n",getpid());        //Current pid
        setpgid(0,0);                   //Change process ground of child
        if(execvp(argv[0],argv) < 0)    //Invalid command
        {
            printf("%d\n",getpid());
            cprint("ERROR: ",RED);
            printf("Invalid Command!!\n");
            exit(0);
        }    
    }
    else
    {
        //printf("Hi,");
        currJob++;
        //printf("%d\n",currJob);
        bgpr newProc;
        newProc.pid = pid;
        newProc.job_number = currJob;
        strcpy(newProc.process,argv[0]);
        AddNodeLL(&newProc,BgProcesses);
        //bgpr *a = BgProcesses;
        // while(a != NULL)
        // {
        //     printf("%d\n",a->pid);
        //     a=a->next;
        // }
        printLL(BgProcesses);
    }
}