#include "shell.h"
#include <grp.h>
#include <pwd.h>

int flagChecker(bool *l, bool *a,int argc, char **argv,char **path)
{
    int cnt = 0;
    for(int i=1; i<argc; i++)
    {   
        if(strcmp("-l",argv[i]) == 0)*l=true;
        else if(strcmp("-a",argv[i]) == 0)*a=true;
        else if(strcmp("-la",argv[i]) == 0)*l=true,*a=true;
        else if(strcmp("-al",argv[i]) == 0)*a=true,*l=true;
        else{
            path[cnt] = malloc(sizeof(char)*(strlen(argv[i])));
            path[cnt][0] = '\0';
            strcpy(path[cnt],argv[i]);
            cnt++;
        }
    }
    return cnt;
}

void ls(int argc, char **argv)
{
    bool l=false, a=false;int cnt = 0;
    char **path = malloc(sizeof(char*)*MAX_PATHS);
    cnt = flagChecker(&l,&a,argc,argv,path);
    if(cnt == 0)
    {
        path[0] = malloc(sizeof(char)*MAX_INP_SIZE);
        path[0][0] = '.';
        path[0][1] = '\0';
        cnt++;
    }
    for(int i=0; i<cnt; i++)
    {
        // path[i][0] = '\0';
        if(path[i][0] == '~')
        {
            if(strlen(path[i]) == 1)
                path[i] = homedir;
            else
            {
                char *temp = malloc(sizeof(char)*MAX_INP_SIZE);
                strcpy(temp,path[i]+2);
                strcpy(homedir,path[i]);
                strcat(path[i], temp);
            }
        }
        DIR *directory;
        struct dirent **namelist; 
        struct stat fileStat;
        struct passwd *user;
        struct group *group;
        char date[40];
        int tot_files = 0;
        int x = scandir(path[i], &namelist, NULL, alphasort);
        if(x == -1)
        {
            if( access(path[i], F_OK ) == 0 ) {
                stat(path[i], &fileStat); 
                user=getpwuid(fileStat.st_uid);
                group=getgrgid(fileStat.st_gid);
                if(l==1)
                {
                    DisplayPerms(fileStat,path[i]);
                    printf(" %-4ld %s %s",fileStat.st_nlink,user->pw_name,group->gr_name);
                    printf(" %-7ld",fileStat.st_size);
                    strftime(date, 35, "%b %d %H:%M", localtime(&fileStat.st_mtime));
                    printf("%-15s ",date);
                }
                if(S_ISDIR(fileStat.st_mode))
                    printf("%s%-15s%s\n",BLU, path[i],RST);
                else
                    printf("%s%-15s%s\n",WHT, path[i],RST); 
            }
            else
            {
                cprint("ERROR: ",RED);
                printf("Given file or directory does not exist!!\n");
            }
            printf("\n");
            continue;
        }
        char temp[MAX_INP_SIZE];
        int tot = 0;
        for(int j=0; j<x; j++)
        { 
            strcpy(temp,path[i]);
            strcat(temp,"/");
            strcat(temp,namelist[j]->d_name);
            stat(temp, &fileStat); 
            tot += fileStat.st_blocks;
            if(!a && namelist[j]->d_name[0] == '.')
                tot -= fileStat.st_blocks;
        }
        if(l || a)
            printf("total %d\n",tot/2);
        for(int j=0; j<x; j++)
        { 
            strcpy(temp,path[i]);
            strcat(temp,"/");
            strcat(temp,namelist[j]->d_name);
            stat(temp, &fileStat); 
            user=getpwuid(fileStat.st_uid);
            group=getgrgid(fileStat.st_gid);
            if(a==0)
                if(namelist[j]->d_name[0] == '.')
                    continue;
            if(l==1)
            {
                DisplayPerms(fileStat,temp);
                printf(" %-4ld %s %s",fileStat.st_nlink,user->pw_name,group->gr_name);
                printf(" %-7ld",fileStat.st_size);
                strftime(date, 35, "%b %d %H:%M", localtime(&fileStat.st_mtime));
                printf("%-15s ",date);
            }
            if(S_ISDIR(fileStat.st_mode))
                printf("%s%-15s%s\n",BLU, namelist[j]->d_name,RST);
            else
                printf("%s%-15s%s\n",WHT, namelist[j]->d_name,RST); 
            free(namelist[j]); 
        } 
        free(namelist);
        printf("\n");
    }
    for(int i=0; i<cnt; i++)
    {
        free(path[i]);
    }
    free(path);
    return ;

}       