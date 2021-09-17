#include "shell.h"

int main()
{
    char *myPrompt = malloc(sizeof(char)*MAX_PROMPT_SIZE);
    char *InputTxt = malloc(sizeof(char)*MAX_INP_SIZE);
    EntersSigchildHandler = false;
    for(int i=0; i<MAX_PROCESSES; i++)
        Process_Array[i].stat = false;
    getcwd(homedir,MAX_DIR_SIZE);
    while(1)
    {
        myPrompt = DisplayPrompt();
        printf("%s",myPrompt);
        fflush(stdout);
        int sig = signal(SIGCHLD,ReturnTerminatedProcess);
        printf("%d\n",sig);
        fgets(InputTxt, MAX_INP_SIZE, stdin);
        InputTxt[strcspn(InputTxt, "\n")] = 0;
        char* token = strtok(InputTxt, ";");
        int ind = -1;
        while (token != NULL) {
            ind++;
            strcpy(inp[ind],token);
            token = strtok(NULL, ";");
        }
        for(int i=0; i<=ind; i++)
        {
            execute_command(inp[i]);
        }
    }
    free(myPrompt); free(InputTxt);
}