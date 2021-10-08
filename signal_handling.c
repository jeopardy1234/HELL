#include "shell.h"

void ReturnTerminatedProcess(int sig)
{
    bgpr *head = BgProcesses->next;
    bgpr *prev = BgProcesses;
    while(head != NULL)
    {
        int stat;
        int waitRet = waitpid(head->pid,&stat,WNOHANG);
        if(waitRet != 0)
        {
            if(!stat)
            {
                printf("\nProcess %s with id %d terminated normally\n",head->process,head->pid);
                printf("%s",DisplayPrompt());
            }
            else
            {
                printf("\nProcess %s with id %d terminated abnormally\n",head->process,head->pid);
                printf("%s",DisplayPrompt());
            }
            prev -> next = head -> next;
            free(head);
            head = prev->next;
        }
        else
        {
            head = head->next;
            prev = prev->next;
        }
    }
    fflush(stdout);
    return ;
}

void signal_control_c(int signal)
{
    if(fg_runnin)
    {
        printf("\n");
        fflush(stdout);
        fg_runnin = false;
        return ;
    }
    char *dis = malloc(MAX_PROMPT_SIZE * sizeof(char));
    printf("\n");
    dis = DisplayPrompt();
    printf("%s", dis);
    fflush(stdout);
}

void signal_control_z(int signal)
{
    char *dis = malloc(MAX_PROMPT_SIZE * sizeof(char));
    printf("\n");
    dis = DisplayPrompt();
    printf("%s", dis);
    fflush(stdout);
}