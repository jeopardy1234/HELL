#include "shell.h"

void cprint(char *s, char* col)
{
    printf("%s",col);
    printf("%s",s);
    printf("%s",RST);
}

