#include "shell.h"

void redirect_input_output(int *argc, char **argv)
{
    char ** NewInput = malloc(sizeof(char) * 513);
    int ind = 0;
    int argu = 0;
    for(int i=0; i<*argc; i++)
    {
        if(strcmp("<", argv[i]) == 0)
        {
            int file = open(argv[i++ + 1],O_RDONLY);
            dup2(file, 0);
            close(file);
        }

        else if(strcmp(">", argv[i]) == 0)
        {
            int file = open(argv[i++ + 1],O_WRONLY|O_CREAT|O_TRUNC, 0644);
            dup2(file, 1);
            close(file);
        }

        else if(strcmp(">>", argv[i]) == 0)
        {
            int file = open(argv[i++ + 1],O_CREAT|O_RDWR|O_APPEND, 0644);
            dup2(file, 1);
            close(file);
        }
        else
        {
            NewInput[ind] = malloc(sizeof(char) * strlen(argv[i]));
            strcpy(NewInput[ind] , argv[i]);
            ind++;
        }
    }
    printf("%d", *argc);
    *argc = ind;
    printf("%d", *argc);
    for(int i=0; i<*argc; i++)
    {
        strcpy(argv[i],NewInput[i]);
    }
    for(int i=0; i<*argc; i++)
    {
        printf("%s ", argv[i]);
        free(NewInput[i]);
    }
    argv[*argc] = NULL;
    printf("\n");
    free(NewInput);
}