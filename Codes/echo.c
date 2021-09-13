#include "shell.h"

void echo(char *token)
{
    //printf("%s",token);
    while (token != NULL) {
        printf("%s ",token);
        token = strtok(NULL, " ");
    }
    printf("\n");
}