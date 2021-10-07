#include "shell.h"

void execute_background(int argc, char **argv)
{
    int pid = fork();       //Create a child process
    argv[argc-1] = NULL;    //else execvp wont work sometimes
    if(pid == 0)
    {
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
        printf("%d\n",pid);        //Current pid
        currJob++;
        bgpr * newProc = malloc(sizeof(bgpr));
        newProc->pid = pid;
        newProc->job_number = currJob;
        strcpy(newProc->process,argv[0]);
        AddNodeLL(newProc,BgProcesses);
    }
}