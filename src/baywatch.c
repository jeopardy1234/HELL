#include "shell.h"

/*
    Use raw mode terminal to exit on key press
    interrupt - /proc/interrupts
    newborn   - /proc/loadavg
    dirty     - /proc/meminfo
    Exit raw mode. Re-enter cooked mode
*/

struct termios orig_termios;
void die(const char *s) {}
void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    die("tcsetattr");
}
void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

void baywatch(int argc, char **argv)
{
    enableRawMode();
    if(argc != 4 || strcmp("-n", argv[1]) != 0 || toDecimal(argv[2]) < 0)
    {
        disableRawMode();
        cprint("ERROR: ",RED);
        printf("Invalid Arguments!!\n");
        return ;
    }
    bool print = false;
    int t_before = time(NULL);
    char *line = malloc(sizeof(char)*4096);
    int col_cnt = 0;
    bool interrupt_first_time = true;
    char c;
    while(1)
    {
        int t_after = time(NULL);
        if(t_after - t_before >= toDecimal(argv[2]))
            print = true;
        size_t len = 0;
        if(strcmp("dirty", argv[3]) == 0)
        {
            if(print)
            {
                FILE *file = fopen("/proc/meminfo" , "r");
                while (getline(&line, &len, file) != -1)
                {
                    if (strncmp(line, "Dirty", 5) == 0)
                    {
                        char *token = strtok(line," \t\v:");
                        token = strtok(NULL," \t\v:"); 
                        printf("%s\r\n",token);
                        break;
                    }
                }
                print = false;
                t_before = t_after;
                fclose(file);
            }
            if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
            if(c == 'q')
                break;
        }

        else if(strcmp("newborn", argv[3]) == 0)
        {
            if(print)
            {
                FILE *file = fopen("/proc/loadavg" , "r");
                getline(&line, &len, file) != -1;
                char *token = strtok(line," \t\v\n");
                char *my_pid = malloc(sizeof(char) * 128);
                int pid_col = 0;
                while(token != NULL)
                {
                    pid_col++;
                    if(pid_col == 5)break;
                    strcpy(my_pid, token);
                    token = strtok(NULL," \t\v\n"); 
                }
                printf("%s\r\n",token);
                print = false;
                t_before = t_after;
                fclose(file);
                free(my_pid);
            }
            if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
            if(c == 'q')
                break;
        }

        else if(strcmp("interrupt", argv[3]) == 0)
        {
            if(interrupt_first_time == true)
            {
                FILE *file = fopen("/proc/interrupts" , "r");
                getline(&line, &len, file);
                char *token = strtok(line," \t\v");
                while(token != NULL)
                {
                    col_cnt++;
                    printf("%s\t", token);
                    token = strtok(NULL," \t\v"); 
                }
                printf("\r\n");
                fclose(file);
                interrupt_first_time = false;
            }
            else if(print)
            {
                FILE *file = fopen("/proc/interrupts" , "r");
                getline(&line, &len, file);
                getline(&line, &len, file);
                getline(&line, &len, file);
                char *token = strtok(line," \t\v");
                int curr_col = -1;
                while(token != NULL)
                {
                    curr_col++;
                    if(curr_col > 0 && curr_col < col_cnt)printf("%s\t", token);
                    token = strtok(NULL," \t\v"); 
                }
                printf("\r\n");
                fclose(file);
                print = false;
                t_before = t_after;
            }
            if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");

            if(c == 'q')
                break;
        }
        else
        {
            cprint("ERROR: ",RED);
            printf("Invalid Arguments!!");
            break;
        }
    }
    free(line);
    disableRawMode();
} 