#include "shell.h"
#include <grp.h>
#include <pwd.h>

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
    struct passwd *user;
    struct group *group;
    directory = opendir(".");
    char date[40];
    int tot_files = 0;
    while((file = readdir(directory)) != NULL)
    {
        tot_files++;
        stat(file->d_name, &fileStat); 
        user=getpwuid(fileStat.st_uid);
        group=getgrgid(fileStat.st_gid);
        if(a==0)
                if(file->d_name[0] == '.')
                    continue;
        if(l==1)
        {
            DisplayPerms(fileStat,file->d_name);
            printf(" %ld %s %s",fileStat.st_nlink,user->pw_name,group->gr_name);
            printf(" %-7ld",fileStat.st_size);
            strftime(date, 35, "%b %d %H:%M", localtime(&fileStat.st_mtime));
            printf("%-15s",date);
        }
        if(S_ISDIR(fileStat.st_mode))
            printf(" %s%-15s%s\n",BLU, file->d_name,RST);
        else
            printf(" %s%-15s%s\n",GRN, file->d_name,RST);
    }
    printf("%d",tot_files);

}