#include "shell.h"
#include <dirent.h>

void cd(int argc, char **argv)
{
    char temp[1024]; //Stores current directory name
    if(argc > 2)     //If args > 2 show error
    {
        cprint("ERROR: ", RED);
        printf("Too many arguments\n");
        return;
    }
    if(argc == 1)
    {
        chdir(homedir);
        strcpy(PrevPath,temp);
        return;
    }
    DIR* dir = opendir(argv[1]);
    if(!dir && strcmp(argv[1],"-") != 0) //incase directory is absent
    {
        cprint("ERROR: ",RED);
        printf("No such file or directory\n");
    }
    if(strcmp(argv[1],".")==0 )
    {
        strcpy(PrevPath,temp);
        return ;
    }
    else
    {
        getcwd(temp,MAX_DIR_SIZE);
        if(argv[1][0] == '~')
        {
            chdir(homedir);
            if(argv[1][1] != '\0')
                chdir(argv[1]+2); // ~/Path, so base + 2
        }
        else if(strcmp(argv[1],"-") == 0)
        {
            if(PrevPath[0] == '\0') //incase cd hasnt been done before
            {
                cprint("ERROR: ", RED);
                printf("OLDPWD not set\n");
                return;
            }
            else
            {
                getcwd(temp,MAX_DIR_SIZE);
                chdir(PrevPath);
                printf("%s\n",PrevPath);
            }
        }
        else
        {
            chdir(argv[1]);
        }
        strcpy(PrevPath,temp);
    }
}