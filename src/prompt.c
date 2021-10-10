#include "shell.h"

char * DisplayPrompt()
{
    char *usr = (char*) malloc(sizeof(char)*MAX_USR_SIZE);
    char *system = (char*)malloc(sizeof(char)*MAX_SYS_SIZE);
    char *curr_dir = (char*)malloc(sizeof(char)*MAX_DIR_SIZE);
    char *prompt_val = (char*)malloc(sizeof(char)*MAX_PROMPT_SIZE);

    getlogin_r(usr,MAX_USR_SIZE);       //Username
    gethostname(system,MAX_SYS_SIZE);   //Kinda device specs
    getcwd(curr_dir,MAX_DIR_SIZE);      //Current dir

    if(strlen(homedir) <= strlen(curr_dir))
    {
        curr_dir[0] = '~';              //Modify home directory
        int x = strlen(homedir);
        for(int i=1; i<x; i++)
        {
            curr_dir[i] = curr_dir[i+x-1];
        }
    }
    sprintf(prompt_val,"<%s%s@%s%s:%s%s>",YEL,usr,system,BLU,curr_dir,RST);
    free(usr);free(system); free(curr_dir);
    return prompt_val;
}