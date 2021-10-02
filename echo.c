#include "shell.h"

/*
    The input is already free of extra whitespaces
    So simply print it
*/

void echo(int argc,char **argv)
{

    for(int i=1; i<argc; i++)
    {
        printf("%s ",argv[i]);
    }
    printf("\n");
}