#include "shell.h"

void pwd(int slen)
{
    if(slen != 3)
    {
        cprint("\nERROR: ", RED);
        printf("pwd takes exactly one argument");
    }
    else
    {
        char *dir = (char*) malloc(sizeof(char)*MAX_DIR_SIZE);
        getcwd(dir,MAX_DIR_SIZE);
        printf("%s\n",dir);
        free(dir);
    }
    return ;
}