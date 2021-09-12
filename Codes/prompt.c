#include "shell.h"

char * DisplayPrompt()
{
    char *usr = (char*) malloc(sizeof(char)*MAX_USR_SIZE);
    char *system = (char*)malloc(sizeof(char)*MAX_SYS_SIZE);
    char *home_dir = (char*)malloc(sizeof(char)*MAX_DIR_SIZE);
    char *prompt_val = (char*)malloc(sizeof(char)*MAX_PROMPT_SIZE);

    getlogin_r(usr,MAX_USR_SIZE);
    gethostname(system,MAX_SYS_SIZE);
    getcwd(home_dir,MAX_DIR_SIZE);

    if(strcmp(home_dir,curr_dir) == 0 || strlen(curr_dir) == 0)
    {
        sprintf(curr_dir,"~");
    }

    sprintf(prompt_val,"<%s%s@%s%s:%s%s>",YEL,usr,system,BLU,curr_dir,RST);
    free(usr);free(system); free(home_dir);
    return prompt_val;
}