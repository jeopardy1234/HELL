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

void exec_pipe(char *command)
{
    char *pipeCommands[MAX_PIPE];
    int numPipes = pipe_splitter(pipeCommands , command);
    int fd[2];
    int input_fd = dup(0);
    int output_fd = dup(1);

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
            pipe(fd);
            output_fd = dup(1);
            dup2(fd[1] , 1);
        }
        int pid = fork();
        if(pid == 0)
        {
            execute_command(pipeCommands[i]);
            exit(0);
        }
        else
        {
            wait(NULL);
            dup2(input_fd,0);
            dup2(output_fd,1);
        }

    }
}