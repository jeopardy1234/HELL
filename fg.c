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
            bgpr *temp = BgProcesses;
            currJob--;
            while(temp != NULL)
            {
                if(temp -> job_number > jb)
                    temp->job_number--;
                temp = temp->next;
            }
            free(temp);
            prev -> next = head -> next;
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(0,getpgid(head->pid));
            kill(head->pid, SIGCONT);

            int status;
            waitpid(head->pid , &status, WUNTRACED);
            tcsetpgrp(0,getpgrp());

            signal(SIGTTOU,SIG_DFL);

            /*Incase fg process stops due to ctrl-z*/
            if(WIFSTOPPED(status))
            {
                currJob++;
                bgpr *node = malloc(sizeof(bgpr));
                node -> pid = head->pid;
                node -> job_number = currJob;
                strcpy(node -> process, head->process);
                AddNodeLL(node, BgProcesses);
                fg_to_bg = 1;
            }

            return;
        }
        head = head->next;
        prev = prev->next;
    }
    cprint("Error: ",RED);
    printf("Job not found\n");
}