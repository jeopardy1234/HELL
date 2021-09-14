/*List of Header Files*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#ifndef SABKA_BAAP_SHELL
#define SABKA_BAAP_SHELL

/*List of Macros*/

/*Colors*/
#define RED  "\x1B[31m"
#define WHT  "\x1B[37m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define GRN  "\x1B[32m"
#define CYN  "\x1B[36m"
#define NRM  "\x1B[0m"
#define RST  "\x1B[0m"

/*Prompt*/
#define MAX_USR_SIZE    1024
#define MAX_SYS_SIZE    1024
#define MAX_DIR_SIZE    1024
#define MAX_PROMPT_SIZE 1024
#define MAX_INP_SIZE    2048

/*Variables*/
char curr_dir[MAX_DIR_SIZE];
char single_inp[512][MAX_INP_SIZE];
char inp[512][MAX_INP_SIZE];
char homedir[MAX_DIR_SIZE];

/*List of Functions*/
void cprint(char *str_input, char* color);
void echo(int argc, char argv[][MAX_INP_SIZE]);
void pwd(int args);
void execute_command(char *s);
void cd(int argc, char argv[][MAX_INP_SIZE]);

char *whitespace_free_input(char *s);
char * DisplayPrompt();

#endif

