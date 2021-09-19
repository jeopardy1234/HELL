#include "shell.h"

int main()
{
    char *myPrompt = malloc(sizeof(char)*MAX_PROMPT_SIZE);
    char *InputTxt = malloc(sizeof(char)*MAX_INP_SIZE);
    PrevPath = malloc(sizeof(char)*MAX_DIR_SIZE);

    PrevPath[0] = '\0';
    for(int i=0; i<MAX_PROCESSES; i++)
        Process_Array[i].stat = false;
    getcwd(homedir,MAX_DIR_SIZE);
    while(1)
    {
        signal(SIGINT, SIG_IGN);
        myPrompt = DisplayPrompt();
        printf("%s",myPrompt);
        fflush(stdout);
        signal(SIGCHLD,ReturnTerminatedProcess);
        fgets(InputTxt, MAX_INP_SIZE, stdin);
        if(strcmp(InputTxt,"\n") == 0)
            continue;
        FILE* history_file = fopen("history.txt","r");
        StoreHistory(InputTxt);
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