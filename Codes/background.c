#include "shell.h"

void execute_background(int argc, char **argv)
{
    int pid = fork();
    argv[argc-1] = NULL;
    if(pid == 0)
    {
        printf("%d\n",getpid());
        setpgid(0,0);
        if(execvp(argv[0],argv) < 0)
        {
            printf("%d\n",getpid());
            cprint("ERROR: ",RED);
            printf("Invalid Command!!\n");
            exit(0);
        }    
    }
    for(int i=0; i<MAX_PROCESSES; i++)
    {
        if(Process_Array[i].stat == false)
        {
            Process_Array[i].stat = true;
            Process_Array[i].pid = pid;
            Process_Array[i].Name = malloc(sizeof(char) * sizeof(argv[0]+1));
            strcpy(Process_Array[i].Name,argv[0]);
            break;
        }
    }
}