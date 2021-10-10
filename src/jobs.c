#include "shell.h"

/*
    Jobs are already inserted in sorted order of proc name
    Check for presence of s and r flags (activate both if none present)
*/

void DisplayJobs(int argc, char **argv)
{
    int r=0,s=0;
    bool rfnd = false, sfnd = false;
    for(int i=1; i<argc; i++)
    {
        if(strcmp("-r", argv[i]) == 0)
        {
            rfnd = true;
            r = 1;
        }
        if(strcmp("-s", argv[i]) == 0)
        {
            sfnd = true;
            s = 1;
        }
    }
    if(!rfnd && !sfnd){
        r=1;
        s=1;
    }
    if((!rfnd && !sfnd && argc > 1) || ((!rfnd || !sfnd) && argc > 2) || (rfnd && sfnd && argc > 3))
    {
        cprint("ERROR: ",RED);
        printf("Too many arguments!!");
    }
    
    bgpr *head = BgProcesses->next;
    char *processInfoPath = malloc(sizeof(char)*MAX_INP_SIZE);
    char *status = malloc(sizeof(char)*MAX_INP_SIZE);
    while (head)
    {
        sprintf(processInfoPath, "/proc/%d/stat", head->pid);
        FILE *file = fopen(processInfoPath,"r");
        if(file == NULL)
        {
            cprint("ERROR: ",RED);printf("Invalid PID!!\n");
            continue;
        }   
        int column = 1;
        while (fscanf(file, "%s",status) == 1)
        {
            if(column == 3)
                break;
            column++;
        }
        if((strcmp(status,"R") == 0 || strcmp(status,"S") == 0) && r == 1) 
        {
            printf("[%d] Running %s [%d]\n", head->job_number, head->process, head->pid);
        }
        else if((strcmp(status,"R") != 0 && strcmp(status,"S") != 0) &&  s == 1)
        {
            printf("[%d] Stopped %s [%d]\n", head->job_number, head->process, head->pid);
        }
        head = head->next;
    }

}