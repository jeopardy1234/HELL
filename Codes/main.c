#include "shell.h"

int main()
{
    char *myPrompt = malloc(sizeof(char)*MAX_PROMPT_SIZE);
    char *InputTxt = malloc(sizeof(char)*MAX_INP_SIZE);
    hisfile = malloc(sizeof(char)*MAX_INP_SIZE);
    //strcpy(hisfile,"/home/jeopardy/historyyy.txt");
    PrevPath = malloc(sizeof(char)*MAX_DIR_SIZE);

    PrevPath[0] = '\0';
    for(int i=0; i<MAX_PROCESSES; i++)
        Process_Array[i].stat = false;
    getcwd(homedir,MAX_DIR_SIZE);       //Permanant variable home directory
    /*Finding the dir of a.out*/
    char *ProcessPath  = malloc(sizeof(char) * MAX_INP_SIZE);
    char *ProcessInfopath = malloc(sizeof(char) * MAX_INP_SIZE);
    int pid = getpid();
    sprintf(ProcessInfopath,"/proc/%d/exe",pid);
    readlink(ProcessInfopath,ProcessPath , MAX_INP_SIZE);
    int LastSlash = (strrchr(ProcessPath,'/')-ProcessPath+1);
    for(int i=0; i<LastSlash; i++)
        strncat(hisfile,&ProcessPath[i],1);
    strcat(hisfile,"history.txt");
    while(1)
    {
        signal(SIGINT, SIG_IGN);        //When a child process terminates
        myPrompt = DisplayPrompt();
        printf("%s",myPrompt);
        fflush(stdout);
        signal(SIGCHLD,ReturnTerminatedProcess);
        fgets(InputTxt, MAX_INP_SIZE, stdin);
        if(strcmp(InputTxt,"\n") == 0)
            continue;
        FILE* history_file = fopen(hisfile,"rw");
        StoreHistory(InputTxt);
        fclose(history_file);
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
            execute_command(inp[i]);
        }
    }
    free(myPrompt); free(InputTxt);
    free(ProcessPath); free(ProcessInfopath);
}