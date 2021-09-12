#include "shell.h"

void pwd(int args)
{
    if(args != 1)
    {
        cprint("\nERROR: ", RED);
        printf("pwd takes exactly one argument");
    }
    else
    {
        char *dir = malloc(sizeof(char)*MAX_DIR_SIZE);
        getcwd(dir,MAX_DIR_SIZE);
        printf("%s",dir);
        free(dir);
    }
    return ;
}