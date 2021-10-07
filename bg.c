#include "shell.h"

void bg(int argc, char **argv)
{
    if(argc != 2)
    {
        cprint("Error: ",RED);
        printf("bg takes exactly 2 arguments!\n");
        return;
    }
    int jb = toDecimal(argv[1]);
    if(jb < 0)
    {
        cprint("Error: ",RED);
        printf("Invalid number\n");
    }
    bgpr *head = BgProcesses->next;
    bgpr *prev = BgProcesses;
    while(head != NULL)
    {
        if(head->job_number == jb)
        {
            if(kill(head->pid, SIGCONT) < 0)
            {
                printf("Failed to continue process\n");
            }
            return;
        }
    }
    cprint("Error: ",RED);
    printf("Job not found\n");
}