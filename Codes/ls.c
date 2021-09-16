#include "shell.h"
#include <grp.h>
#include <pwd.h>

int flagChecker(bool *l, bool *a,int argc, char **argv, char *path)
{
    int cnt = 0;
    for(int i=1; i<argc; i++)
    {   
        if(strcmp("-l",argv[i]) == 0)*l=true;
        else if(strcmp("-a",argv[i]) == 0)*a=true;
        else if(strcmp("-la",argv[i]) == 0)*l=true,*a=true;
        else if(strcmp("-al",argv[i]) == 0)*a=true,*l=true;
        else{
            cnt++;
            strcpy(path,argv[i]);
        }
    }
    return cnt;
}

void ls(int argc, char **argv)
{
    bool l=false, a=false;int cnt = 0;
    char *path = malloc(sizeof(char)*MAX_INP_SIZE);
    path[0] = '\0';
    cnt = flagChecker(&l,&a,argc,argv,path);
    if(cnt > 1)
    {
        cprint("ERROR: ", RED);
        printf("Too many arguments\n");
        return;
    }
    if(path[0] == '\0')
        path = ".";
    
    else
    {
        if(path[0] == '~')
        {
            if(strlen(path) == 1)
                path = homedir;
            else
            {
                char *temp = malloc(sizeof(char)*MAX_INP_SIZE);
                strcpy(temp,path+2);
                strcpy(homedir,path);
                strcat(path, temp);
            }
        }
    }
    DIR *directory;
    struct dirent **namelist; 
    struct stat fileStat;
    struct passwd *user;
    struct group *group;
    char date[40];
    int tot_files = 0;
    int x = scandir(path, &namelist, NULL, alphasort);
    if(x == -1)
    {
        if( access(path, F_OK ) == 0 ) {
            stat(path, &fileStat); 
            user=getpwuid(fileStat.st_uid);
            group=getgrgid(fileStat.st_gid);
            if(l==1)
            {
                DisplayPerms(fileStat,path);
                printf(" %ld %s %s",fileStat.st_nlink,user->pw_name,group->gr_name);
                printf(" %-7ld",fileStat.st_size);
                strftime(date, 35, "%b %d %H:%M", localtime(&fileStat.st_mtime));
                printf("%-15s",date);
            }
            if(S_ISDIR(fileStat.st_mode))
                printf(" %s%-15s%s\n",BLU, path,RST);
            else
                printf(" %s%-15s%s\n",WHT, path,RST); 
        }
        else
        {
            cprint("ERROR: ",RED);
            printf("Given file or directory does not exist!!\n");
        }
        return;
    }
    char temp[MAX_INP_SIZE];
    printf("Total files: %d\n",x);
    while (x--) 
	{ 
        strcpy(temp,path);
        strcat(temp,"/");
        strcat(temp,namelist[x]->d_name);
        stat(temp, &fileStat); 
        user=getpwuid(fileStat.st_uid);
        group=getgrgid(fileStat.st_gid);
        if(a==0)
            if(namelist[x]->d_name[0] == '.')
                continue;
        if(l==1)
        {
            DisplayPerms(fileStat,temp);
            printf(" %ld %s %s",fileStat.st_nlink,user->pw_name,group->gr_name);
            printf(" %-7ld",fileStat.st_size);
            strftime(date, 35, "%b %d %H:%M", localtime(&fileStat.st_mtime));
            printf("%-15s",date);
        }
        if(S_ISDIR(fileStat.st_mode))
            printf(" %s%-15s%s\n",BLU, namelist[x]->d_name,RST);
        else
            printf(" %s%-15s%s\n",WHT, namelist[x]->d_name,RST); 
        free(namelist[x]); 
	} 
    free(namelist);

}