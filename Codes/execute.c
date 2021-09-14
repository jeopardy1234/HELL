#include "shell.h"

void execute_command(char *s)
{
    //s = whitespace_free_input(s);
    char* token = strtok(s, " \t\v");
    int ind = -1;
    while (token != NULL) {
        ind++;
        strcpy(single_inp[ind],token);
        token = strtok(NULL, " \t\v");
    }
    if(strcmp(single_inp[0],"pwd") == 0)
        pwd(ind+1);
    else if(strcmp(single_inp[0],"echo") == 0)
        echo(ind+1,single_inp);
    else if(strcmp(single_inp[0],"cd") == 0)
        cd(ind+1,single_inp);
}