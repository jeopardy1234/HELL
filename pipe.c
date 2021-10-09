#include "shell.h"

int pipe_splitter(char *pipe_splitted[MAX_PIPE], char *command)
{
    int num_pipes = -1;
    char *token = strtok(command,"|");
    while(token != NULL)
    {
        num_pipes++;
        pipe_splitted[num_pipes] = malloc(sizeof(char) * MAX_INP_SIZE);
        strcpy(pipe_splitted[num_pipes], token);
        token = strtok(NULL,"|"); 
    }
    return num_pipes;
}

bool exec_pipe(char *command)
{
    char *pipeCommands[MAX_PIPE];
    char *temp = malloc(sizeof(char) * MAX_INP_SIZE);
    strcpy(temp, command);
    char *tokcheck = strtok(temp, " \t\v");
    if(strcmp(tokcheck, "replay") == 0)return false;
    int numPipes = pipe_splitter(pipeCommands , command);
    int fd[2];
    int input_fd = dup(0);
    int output_fd = dup(1);
    if(numPipes == 0)
        return false;
    for(int i=0; i<=numPipes; i++)
    {
        if(i!=0)
        {
            close(fd[1]);
            input_fd = dup(0);
            dup2(fd[0],0);
            close(fd[0]);
        }
        if(i != numPipes)
        {
            if(pipe(fd) < 0)
            {
                cprint("ERROR: ",RED);
                printf("Invalid Piping!");
            }
            dup2(fd[1] , 1);
        }

        execute_command(pipeCommands[i]);
        dup2(input_fd,0);
        dup2(stou,1);

    }
    return true;
}