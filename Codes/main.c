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
        InputTxt = whitespace_free_input(InputTxt);
        printf("%s\n",InputTxt);
    }
    free(myPrompt); free(InputTxt);
}