#include "shell.h"

void sig(int argc, char **argv)
{
    if(argc != 3)
    {
        cprint("Error: ",RED);
        printf("sig takes exactly 2 arguments!\n");
        return;
    }
    int jb = toDecimal(argv[1]);
    int signal = toDecimal(argv[2]);
    if(jb < 0)
    {
        cprint("Error: ",RED);
        printf("Invalid job number\n");
    }
    if(jb < 0)
    {
        cprint("Error: ",RED);
        printf("Invalid signal number\n");
    }
    bgpr *head = BgProcesses->next;
    bgpr *prev = BgProcesses;
    while(head != NULL)
    {
        if(head->job_number == jb)
        {
            if(kill(head->pid, signal) < 0)
            {
                cprint("Error: ",RED);
                printf("Invalid signal number\n");
            }
            return;
        }
        head = head->next;
        prev = prev->next;
    }
    cprint("Error: ",RED);
    printf("Job not found\n");
}