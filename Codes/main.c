#include "shell.h"

char inp[512][MAX_INP_SIZE];

int main()
{
    char *myPrompt = malloc(sizeof(char)*MAX_PROMPT_SIZE);
    char *InputTxt = malloc(sizeof(char)*MAX_INP_SIZE);
    while(1)
    {
        myPrompt = DisplayPrompt();
        printf("%s",myPrompt);

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