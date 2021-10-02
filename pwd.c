#include "shell.h"

void pwd(int args)
{
    if(args != 1)
    {
        cprint("ERROR: ", RED);
        printf("Too many arguments\n");
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