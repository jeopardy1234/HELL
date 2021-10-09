/*List of Header Files*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>
#include <termios.h>
#include <errno.h>

#ifndef SABKA_BAAP_SHELL
#define SABKA_BAAP_SHELL

typedef struct proc{
    int pid;
    char *Name;
    bool stat; //0 for passive, 1 for active
}process;
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
#define MAX_PATHS       512
#define MAX_PIPE        64

/*Misc*/
#define MAX_PROCESSES   1024

/*Structs*/
typedef struct BackgroundProcess{
    pid_t pid;
    int job_number;
    char process[128];
    struct BackgroundProcess* next;
}bgpr;


/*Variables*/
char curr_dir[MAX_DIR_SIZE];
char inp[512][MAX_INP_SIZE];
char homedir[MAX_DIR_SIZE];
process Process_Array[1024];
bgpr *BgProcesses;
bool EntersSigchildHandler;
/*List of Functions*/
void cprint(char *str_input, char* color);
void echo(int argc, char **argv);
void pwd(int args);
void execute_command(char *s);
void cd(int argc, char **argv);
void DisplayPerms(struct stat fileStat, char *fileName);
void ls(int argc, char **argv);
void execute_foreground(int argc, char **argv);
void execute_background(int argc, char **argv);
void ReturnTerminatedProcess(int sig);
void execute_whitespace_Separated(char **single_inp, int argc);
void repeat(int argc, char **argv);
void pinfo(int argc, char **argv);
void DisplayHistory(int argc, char**argv);
void baywatch(int argc, char **argv);
void StoreHistory(char *s);
void redirect_input_output(int *argc, char **argv);
void fg(int argc, char **argv);
void bg(int argc, char **argv);
void sig(int argc, char **argv);
void DisplayJobs(int argc, char **argv);
void replay(int argc, char **argv);
void signal_control_c(int sig);
void initializeLL(bgpr *head);
void AddNodeLL(bgpr *node, bgpr *head);
void signal_control_z(int signal);
void printLL(bgpr *head);

int toDecimal(char *s);
bool exec_pipe(char *command);

char * DisplayPrompt();
char *PrevPath;
char *hisfile;

int stin;
int stou;
int currJob;
int fg_runnin;
int fg_to_bg;

#endif

