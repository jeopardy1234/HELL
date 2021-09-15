#include "shell.h"
#include <dirent.h>

void cd(int argc, char argv[][MAX_INP_SIZE])
{
    if(argc > 2)
    {
        cprint("ERROR: ", RED);
        printf("Too many arguments\n");
        return;
    }
    if(argc == 1)
    {
        chdir(homedir);
        return;
    }
    if(strcmp(argv[1],".")==0)return;
    else
    {
        if(argv[1][0] != '~')
            chdir(argv[1]);
        else
        {
            chdir(homedir);
            if(argv[1][1] != '\0')
                chdir(argv[1]+2);
        }
    }
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    
}