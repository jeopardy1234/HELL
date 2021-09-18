#include "shell.h"

int toDecimal(char *s)
{
    int x = strlen(s);
    int ans = 0;
    for(int i=0;i<x; i++)
    {
        int p = s[i] - '0';
        if(p >= 0 && p <= 9)
        {
            ans = ans*10+p;
        }
        else
            return -1;
    }
    return ans;
}

void pinfo(int argc, char **argv)
{
    char *path = malloc(sizeof(char) * MAX_INP_SIZE);
    char *loc  = malloc(sizeof(char) * MAX_INP_SIZE);
    char *buffer = memalloc_str(MAX_INP_SIZE);
    char *line = memalloc_str(MAX_INP_SIZE);
    pid_t pid;
    if(argv[1] == NULL)
        pid = getpid();
    else
        pid = toDecimal(argv[1]);
    sprintf(path, "/proc/%d/status", pid);
    sprintf(buffer, "pid -- %s\n", pid);
    printf("%s\n",buffer);
    size_t sz = 0;
    FILE *file = fopen(path, "r");
    while (getline(&line, &sz, file) != -1)
    {
        if (strncmp("State", line, 5) == 0)
        {
            printf("Process Status -- ");
            int cur = 0;
            for (int i = 7; line[i] != '\0'; i++, cur++)
                buffer[cur] = line[i];
            buffer[cur] = '\0';
            printf("%s",buffer);
        }
        else if (strncmp("VmSize", line, 6) == 0)
        {
            printf("memory -- ");
            int cur = 0;
            for (int i = 8; line[i] != '\0'; i++, cur++)
                buffer[cur] = line[i];
            buffer[cur] = '\0';
            printf("%s",buffer);
        }
    }
    fclose(file);
    sprintf(loc,"/proc/%d/exe",pid);
    int ln = readlink(loc,path,MAX_INP_SIZE);
    path[ln] = '\0';
    if(strlen(homedir) <= strlen(path))
    {
        path[0] = '~';
        int x = strlen(homedir);
        for(int i=1; i<x; i++)
        {
            path[i] = path[i+x-1];
        }
    }
    printf("Executable path -- %s\n",path);
}