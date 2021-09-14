#include <stdio.h>

int main()
{
    char *s = "hello";
    char *p = s;
    s = "bye";
    printf("%s %s",p,s);
}