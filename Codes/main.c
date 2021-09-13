#include "shell.h"

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
        while (token != NULL) {
            execute_command(token);
            token = strtok(NULL, "-");
        }
    }
    free(myPrompt); free(InputTxt);
}