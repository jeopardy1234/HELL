#include "shell.h"

int main(int argc, char **argv)
{
    char *s = malloc(sizeof(char)*MAX_INP_SIZE);
    s = whitespace_free_input("h   o    l a     p");   
}