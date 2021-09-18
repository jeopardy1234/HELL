/*
/proc/pid/stat
Column 1  : PID
Column 3  : Status
Column 23 : Virtual Memory
*/
#include "shell.h"

void pinfo(int argc, char **argv)
{
    char *ProcessInfopath = malloc(sizeof(char) * MAX_INP_SIZE);
    char *ProcessPath  = malloc(sizeof(char) * MAX_INP_SIZE);
    char *memory = malloc(sizeof(char)*MAX_INP_SIZE);
    char *TakeLine = malloc(sizeof(char)*MAX_INP_SIZE);
    char *status = malloc(sizeof(char)*MAX_INP_SIZE);

    char **ColumnSplitted = malloc(sizeof(char*)*MAX_INP_SIZE);
    pid_t pid;
    if(argv[1] == NULL)
        pid = getpid();
    else
        pid = toDecimal(argv[1]);
    sprintf(ProcessInfopath, "/proc/%s/status", argv[1]);

    FILE *file = fopen( ProcessInfopath,"r");
    if(file == NULL)
    {
        cprint("ERROR: ",RED);printf("Invalid PID!!\n");
        return;
    }

    

    if(strlen(homedir) <= strlen(ProcessPath))
    {
        ProcessPath[0] = '~';
        int x = strlen(homedir);
        for(int i=1; i<x; i++)
        {
            ProcessPath[i] = ProcessPath[i+x-1];
        }
    }
    printf("Executable Path-- %s\n",ProcessPath);
}