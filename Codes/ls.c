#include "shell.h"

int flagChecker(bool *l, bool *a,int argc, char argv[][MAX_INP_SIZE])
{
    int cnt = 0;
    for(int i=0; i<argc; i++)
    {   
        if(strcmp("-l",argv[i]) == 0)*l=true;
        else if(strcmp("-a",argv[i]) == 0)*a=true;
        else if(strcmp("-la",argv[i]) == 0)*l=true,*a=true;
        else if(strcmp("-al",argv[i]) == 0)*a=true,*l=true;
        else cnt++;
    }
    return cnt;
}

void ls(int argc, char argv[][MAX_INP_SIZE])
{
    bool l=false, a=false;int cnt = 0;
    cnt = flagChecker(&l,&a,argc,argv);
    if(cnt > 2)
    {
        cprint("ERROR: ", RED);
        printf("Too many arguments\n");
        return;
    }
    DIR *directory;
    struct dirent *file;
    struct stat fileStat;

    directory = opendir(".");
    char date[40];
    while((file = readdir(directory)) != NULL)
    {
        stat(file->d_name, &fileStat); 
        if(l == true)DisplayPerms(fileStat,file->d_name);
        printf(" %-15s", file->d_name);
        if(l==false){printf("\n");continue;}   
        printf("%-7ld",fileStat.st_size);
        strftime(date, 35, "%b %d %H:%M", localtime(&fileStat.st_mtime));
        printf("%-12s\n",date);
    }

}