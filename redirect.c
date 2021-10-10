#include "shell.h"

bool redirect_input_output(int *argc, char **argv)
{
    char ** NewInput = malloc(sizeof(char) * 513);
    bool retVal = true;
    int ind = 0;
    int argu = 0;
    for(int i=0; i<*argc; i++)
    {
        if(i == *argc-1 && (strcmp(argv[i] , ">") == 0 || strcmp(argv[i] , "<") == 0 || strcmp(argv[i] , ">>") == 0))
        {
            cprint("ERROR: ",RED);
            printf("Unexpected redirection near newline!!\n");
            retVal = false;
            break;
        }
        if(strcmp("<", argv[i]) == 0)
        {
            int file = open(argv[i++ + 1],O_RDONLY);
            if(file < 0)
            {
                cprint("ERROR: ",RED);
                printf("File doesn't exist!!\n");
                return false;
            }
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

    *argc = ind;
    for(int i=0; i<*argc; i++)
    {
        strcpy(argv[i],NewInput[i]);
    }
    for(int i=0; i<*argc; i++)
    {
        free(NewInput[i]);
    }
    argv[*argc] = NULL;
    free(NewInput);
    return retVal;
}