#include "shell.h"

int toDecimal(char *s)
{
    int x = strlen(s);
    int ans = 0;
    for(int i=0;i<x; i++)
    {
        int p = s[i] - '0';
        if(p >= 0 && p <= 9)
        {
            ans = ans*10+p;
        }
        else
            return -1;
    }
    return ans;
}

void repeat(int argc, char **argv)
{
    if(argc < 3)    //Atleast 3 args required
    {
        cprint("ERROR: ", RED);
        printf("repeat is missing some arguments\n");
        return ;
    }
    int HowMany = toDecimal(argv[1]); //Frequency
    if(HowMany == -1)
    {
        cprint("repeat: ", RED);
        printf("parameter 2 is not a NaN\n");
        return ;
    }
    for(int i=0; i<HowMany; i++)
    {
        execute_whitespace_Separated(&argv[2],argc-2); //repeat [freq] [stuff]
                                                       //Stuff is at argv[2]
    }
} 