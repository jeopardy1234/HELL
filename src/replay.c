#include "shell.h"

void replay(int argc, char **argv)
{
    int interval=-1, time_period=-1;
    char *command = malloc(MAX_INP_SIZE);
    for(int i=1; i<argc; i++)
    {
        if(strcmp(argv[i],"-interval") == 0)
        {
            interval = toDecimal(argv[i++ + 1]);
        }
        else if(strcmp(argv[i],"-period")==0)
            time_period = toDecimal(argv[i++ + 1]);
        else if(strcmp(argv[i],"-command")==0)
        {
            i++;
            while(i < argc && strcmp(argv[i],"-interval") != 0 && strcmp(argv[i],"-interval") != 0)
            {
                strcat(command, argv[i]);
                strcat(command, " ");
                i++;
            }
            i--;
        }
    }
    if(interval <= 0)
    {
        cprint("ERROR: ", RED);
        printf("Interval MUST be a natural number!!\n");
        free(command);
        return ;
    }
    if(time_period <= 0)
    {
        cprint("ERROR: ", RED);
        printf("Time Period MUST be a natural number!!\n");
        free(command);
        return ;
    }
    char s[MAX_INP_SIZE];
    for(int i=0; i<time_period/interval; i++)
    {
        strcpy(s, command);
        sleep(interval);
        bool isPipe = exec_pipe(s);
        if(!isPipe)
            execute_command(s);
        dup2(stin,STDIN_FILENO);
        dup2(stou,STDOUT_FILENO);
    }
}