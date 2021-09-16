#include "shell.h"

int main()
{
   char *args[] = {"ls","-la","..",NULL};
    execvp("ls",args);
}