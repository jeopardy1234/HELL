#ifndef SXY_COLORS
#define SXY_COLORS

#include<stdio.h>

#define RED  "\x1B[31m"
#define WHT  "\x1B[37m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define GRN  "\x1B[32m"
#define CYN  "\x1B[36m"
#define NRM  "\x1B[0m"
#define RST  "\x1B[0m"

void cprint(char *s, char* col);

#endif