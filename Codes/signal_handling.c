#include "shell.h"

void ReturnTerminatedProcess(int sig)
{
    int stat;
    for(int i=0; i<MAX_PROCESSES;  i++)
    {
        if(Process_Array[i].stat)
        {
            int waitRet = waitpid(Process_Array[i].pid,&stat,WNOHANG);
            if(waitRet == 0)
                continue;
            if(!stat)
            {
                printf("\nProcess %s with id %d terminated normally\n",Process_Array[i].Name,Process_Array[i].pid);
                printf("%s",DisplayPrompt());
            }
            else
            {
                printf("\nProcess %s with id %d terminated abnormally\n",Process_Array[i].Name,Process_Array[i].pid);
                printf("%s",DisplayPrompt());
            }
            Process_Array[i].stat = false;
            free(Process_Array[i].Name);
        }
    }
    fflush(stdout);
    return ;
}