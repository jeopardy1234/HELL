#include "shell.h"

void execute_command(char *s)
{
    //s = whitespace_free_input(s);
    char ** single_inp =  malloc(sizeof(char*)*513);
    char* token = strtok(s, " \t\v");
    int ind = -1;
    while (token != NULL) {
        ind++;
        single_inp[ind] = malloc(sizeof(char)*(strlen(token)+1));
        strcpy(single_inp[ind],token);
        token = strtok(NULL, " \t\v");
    }
    single_inp[ind+1] = NULL;
    if(strcmp(single_inp[0],"pwd") == 0)
        pwd(ind+1);
    else if(strcmp(single_inp[0],"echo") == 0)
        echo(ind+1,single_inp);
    else if(strcmp(single_inp[0],"cd") == 0)
        cd(ind+1,single_inp);
    else if(strcmp(single_inp[0],"ls") == 0)
        ls(ind+1,single_inp);
    else
    {
        if(strcmp("&",single_inp[ind]) == 0)
        {
            execute_background(ind+1,single_inp);
        }
        else
            execute_foreground(ind+1,single_inp);
    }
    for(int i=0;i<=ind;i++)
        free(single_inp[i]);
    free(single_inp);
}