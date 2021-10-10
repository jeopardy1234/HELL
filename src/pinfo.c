/*
/proc/[pid]/stat
Column 1  : PID
Column 3  : Status
Column 5  : pgrp
Column 8   : tgrp
Column 23 : Virtual Memory (bits)

Idea : PID is trivial
For Status, take it from column 3
If pgrp = tgrp, its foreground so add +
Take Memory from column 23
For path use readlink
*/
#include "shell.h"

void pinfo(int argc, char **argv)
{
    char *ProcessInfopath = malloc(sizeof(char) * MAX_INP_SIZE);
    char *ProcessPath  = malloc(sizeof(char) * MAX_INP_SIZE);
    char *memory = malloc(sizeof(char)*MAX_INP_SIZE);
    char *status = malloc(sizeof(char)*MAX_INP_SIZE);
    char *pgrp = malloc(sizeof(char)*MAX_INP_SIZE);
    char *tgrp = malloc(sizeof(char)*MAX_INP_SIZE);
    char *pid_str = malloc(sizeof(char)*MAX_INP_SIZE);
    char str[MAX_INP_SIZE];
    pid_t pid;
    if(argv[1] == NULL)
        pid = getpid();
    else
        pid = toDecimal(argv[1]);
    sprintf(ProcessInfopath, "/proc/%d/stat", pid);

    FILE *file = fopen( ProcessInfopath,"r");
    if(file == NULL)
    {
        cprint("ERROR: ",RED);printf("Invalid PID!!\n");
        return;
    }
    int column = 1;
    while (fscanf(file, "%s", str) == 1)
    {
        if(column == 1)
            strcpy(pid_str,str);
        else if(column == 3)
            strcpy(status,str);
        else if(column == 5)
            strcpy(pgrp,str);
        else if(column == 8)
            strcpy(tgrp,str);
        else if(column == 23)
            strcpy(memory,str);
        column++;
    }
    fclose(file);
    if(strcmp(pgrp,tgrp) == 0)
        strcat(status,"+");
    strcpy(ProcessInfopath,"/proc/");
    strcat(ProcessInfopath,pid_str);
    strcat(ProcessInfopath,"/exe");
    readlink(ProcessInfopath,ProcessPath , MAX_INP_SIZE);
    if(strlen(homedir) <= strlen(ProcessPath))
    {
        ProcessPath[0] = '~';
        int x = strlen(homedir);
        for(int i=1; i<x; i++)
        {
            ProcessPath[i] = ProcessPath[i+x-1];
        }
    }
    printf("pid -- %s\n", pid_str);
    printf("Process Status -- %s\n", status);
    printf("memory -- %s(bytes) {​Virtual Memory​}\n", memory);
    printf("Executable Path -- %s\n", ProcessPath);
    free(ProcessInfopath);free(ProcessPath);free(memory);free(tgrp);
    free(pgrp);free(pid_str);free(status);
}