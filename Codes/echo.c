#include "shell.h"

void echo(int argc,char argv[][MAX_INP_SIZE])
{
    //printf("%s",token);
    for(int i=1; i<argc; i++)
    {
        printf("%s ",argv[i]);
    }
    printf("\n");
}