#include "shell.h"

int main()
{
    BgProcesses = malloc(sizeof(bgpr));
    BgProcesses->next = NULL;
    currJob = 0;fg_runnin = 0;fg_to_bg=0;
    char *myPrompt = malloc(sizeof(char)*MAX_PROMPT_SIZE);
    char *InputTxt = malloc(sizeof(char)*MAX_INP_SIZE);
    hisfile = malloc(sizeof(char)*MAX_INP_SIZE);
    PrevPath = malloc(sizeof(char)*MAX_DIR_SIZE);
    char *usr = (char*) malloc(sizeof(char)*MAX_USR_SIZE);

    PrevPath[0] = '\0';
    getcwd(homedir,MAX_DIR_SIZE);       //Permanant variable home directory
    /*Finding the dir of a.out*/
    char *ProcessPath  = malloc(sizeof(char) * MAX_INP_SIZE);
    char *ProcessInfopath = malloc(sizeof(char) * MAX_INP_SIZE);
    getlogin_r(usr,MAX_USR_SIZE);
    int pid = getpid();
    sprintf(ProcessInfopath,"/proc/%d/exe",pid);
    readlink(ProcessInfopath,ProcessPath , MAX_INP_SIZE);
    strcat(hisfile,"/home/");
    strcat(hisfile, usr);
    strcat(hisfile,"/history_hell_jeo007.txt");

    stin = dup(STDIN_FILENO);
    stou = dup(STDOUT_FILENO);

    signal(SIGINT, signal_handler_c);
    signal(SIGTSTP, signal_handler_z);
    signal(SIGCHLD,ReturnTerminatedProcess);

    char buffer[MAX_INP_SIZE];

    while(1)
    {
        char buffer[MAX_INP_SIZE];
        myPrompt = DisplayPrompt();
        printf("%s",myPrompt);
        fflush(stdout);
        if(fgets(InputTxt, MAX_INP_SIZE, stdin) == NULL)
        {
            printf("\n");
            free(myPrompt); free(InputTxt);
            free(ProcessPath); free(ProcessInfopath);
            exit(0);
        }
        if(strcmp(InputTxt,"\n") == 0)
            continue;
        int history_file = open(hisfile, O_APPEND|O_CREAT,777);
        StoreHistory(InputTxt);
        close(history_file);
        InputTxt[strcspn(InputTxt, "\n")] = 0;
        if(strcmp("quit",InputTxt) == 0)
            return 0;
        char* token = strtok(InputTxt, ";");
        int ind = -1;
        while (token != NULL) {
            ind++;
            strcpy(inp[ind],token);
            token = strtok(NULL, ";");
        }
        for(int i=0; i<=ind; i++)
        {
            bool comm = exec_pipe(inp[i]);
            if(!comm)
                execute_command(inp[i]);
            dup2(stin,STDIN_FILENO);
            dup2(stou,STDOUT_FILENO);
        }
    }
    free(myPrompt); free(InputTxt);
    free(ProcessPath); free(ProcessInfopath);
}