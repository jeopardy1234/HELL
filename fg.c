#include "shell.h"

void fg(int argc, char **argv)
{
    if(argc != 2)
    {
        cprint("Error: ",RED);
        printf("fg takes exactly 2 arguments!\n");
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
            prev -> next = head -> next;
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(0,getpgid(head->pid));
            kill(head->pid, SIGCONT);

            int status;
            waitpid(head->pid , &status, WUNTRACED);
            tcsetpgrp(0,getpgrp());

            signal(SIGTTOU,SIG_DFL);

            return;
        }
        head = head->next;
        prev = prev->next;
    }
    printf("Job not found\n");
}