#include "shell.h"
#include <ctype.h>
char *whitespace_free_input(char *s)
{
    char *buffer = (char*)malloc(sizeof(char)*MAX_INP_SIZE);
    buffer[0] = '\0';
    bool can_we_add_char = false;
    for(int i=0;i < strlen(s); i++)
    {
        if(isspace(s[i]))
        {
            if(can_we_add_char){
                strcat(buffer, " ");
                can_we_add_char = false;
            }
            continue;
        }
        strncat(buffer, &s[i], 1);
        can_we_add_char = true;
    }
    return buffer;
}