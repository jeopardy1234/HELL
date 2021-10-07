#include "shell.h"

void ReturnTerminatedProcess(int sig)
{
    // int stat;
    // for(int i=0; i<MAX_PROCESSES;  i++)
    // {
    //     if(Process_Array[i].stat)
    //     {
    //         //WNOHANG wont really wait for the process to complete
    //         //Reaps without waiting
    //         int waitRet = waitpid(Process_Array[i].pid,&stat,WNOHANG);
    //         if(waitRet == 0)
    //             continue;
    //         if(!stat)
    //         {
    //             printf("\nProcess %s with id %d terminated normally\n",Process_Array[i].Name,Process_Array[i].pid);
    //             printf("%s",DisplayPrompt());
    //         }
    //         else
    //         {
    //             printf("\nProcess %s with id %d terminated abnormally\n",Process_Array[i].Name,Process_Array[i].pid);
    //             printf("%s",DisplayPrompt());
    //         }
    //         Process_Array[i].stat = false;
    //         free(Process_Array[i].Name);
    //     }
    // }
    // bgpr *head = BgProcesses->next;
    // bgpr *prev = BgProcesses;
    // while(head != NULL)
    // {
    //     int stat;
    //     int waitRet = waitpid(head->pid,&stat,WNOHANG);
    //     if(waitRet != 0)
    //     {
    //         if(!stat)
    //         {
    //             printf("\nProcess %s with id %d terminated normally\n",head->process,head->pid);
    //             printf("%s",DisplayPrompt());
    //         }
    //         else
    //         {
    //             printf("\nProcess %s with id %d terminated abnormally\n",head->process,head->pid);
    //             printf("%s",DisplayPrompt());
    //         }
    //         prev -> next = head -> next;
    //         free(head);
    //         head = prev->next;
    //     }
    //     else
    //     {
    //         head = head->next;
    //         prev = prev->next;
    //     }
    // }
    // fflush(stdout);
    // return ;z
}

void signal_control_c(int signal)
{
	printf("\n");
	char *dis = malloc(MAX_PROMPT_SIZE * sizeof(char));
    DisplayPrompt(dis);
    printf("%s",dis);

	fflush(stdout);
}