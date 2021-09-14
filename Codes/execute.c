#include "shell.h"

char single_inp[512][MAX_INP_SIZE];
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
}