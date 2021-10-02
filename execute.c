#include "shell.h"

/*Executes the extra whitespace free inputs*/
void execute_whitespace_Separated(char **single_inp, int argc)
{
    single_inp[argc] = NULL;
    redirect_input_output(&argc,single_inp);
    if(strcmp(single_inp[0],"pwd") == 0)
        pwd(argc);
    else if(strcmp(single_inp[0],"echo") == 0)
        echo(argc,single_inp);
    else if(strcmp(single_inp[0],"cd") == 0)
        cd(argc,single_inp);
    else if(strcmp(single_inp[0],"ls") == 0)
        ls(argc,single_inp);
    else if(strcmp(single_inp[0],"repeat") == 0)
        repeat(argc,single_inp);
    else if(strcmp(single_inp[0],"pinfo") == 0)
        pinfo(argc,single_inp);
    else if(strcmp(single_inp[0],"history") == 0)
    {
        DisplayHistory(argc,single_inp);
    }
    else
    {
        if(strcmp("&",single_inp[argc-1]) == 0)
            execute_background(argc,single_inp);
        else
            execute_foreground(argc,single_inp);
    }
}

void execute_command(char *s)
{
    //s = whitespace_free_input(s);
    char ** single_inp =  malloc(sizeof(char*)*513);    //Not more than 512 semicolons
    char* token = strtok(s, " \t\v");                   //Remove the unnecessary whitespaces
    int ind = -1;                                  
    while (token != NULL) {
        ind++;
        single_inp[ind] = malloc(sizeof(char)*(strlen(token)+1));
        strcpy(single_inp[ind],token);
        token = strtok(NULL, " \t\v");
    }
    execute_whitespace_Separated(single_inp,ind+1);     //Execute the whitespace free inputs
    for(int i=0;i<=ind;i++)
        free(single_inp[i]);
    free(single_inp);
}