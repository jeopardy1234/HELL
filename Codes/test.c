#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "shell.h"
int main()
{
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;

    mydir = opendir(".");
    while((myfile = readdir(mydir)) != NULL)
    {
        stat(myfile->d_name, &mystat);    
        DisplayPerms(mystat,myfile->d_name);
        printf("%ld",mystat.st_size);
        printf(" %s\n", myfile->d_name);
    }
    closedir(mydir);
}