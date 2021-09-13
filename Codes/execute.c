#include "shell.h"

void execute_command(char *s)
{
    whitespace_free_input(s);
    char* token = strtok(s, " ");
    // while (token != NULL) {
    //     printf("%s\n", token);
    //     token = strtok(NULL, " ");
    // }
    if(strcmp(token,"pwd") == 0)
        pwd(strlen(s));
    else if(strcmp(token,"echo") == 0)
        echo(token = strtok(NULL, " "));
}