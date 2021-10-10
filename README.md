# (S)Hell

## To Run:

> make
>
> ./hell

To exit the shell, use `quit` or `ctrl-D`
## Assumptions:

- There are appropriate permissions to create a file at the location - `/home/[user]`.  A file named `history_hell_jeo007.txt` will be created.

- Number of semicolon separated inputs is max 512 characters
- Hostname size if max 512 characters
- Max size of input is not more than 2048 characters at once
- history.txt file won't be deleted while running the shell
- `>` always refers to redirection, and has whitespaces around it (something like `command>file` wont work, use `command > file` instead.

## Features :

- Supports piping and redirection
- Supports multiple `;` separated commands
- Supports signal handling for `SIGCHLD`, `SIGINT` and `SIGTSTP` signals.

## Supported Commands:

### cd:

- To switch between directories
- If no argument is provided - It goes to the home directory

### ls:

- To list the contents of the directory
- Supported flags - `-l` and `-a`

### pwd:

- To print the path of currenntly working directory

###  echo:

- Prints the input string to the tty

### pinfo:

- Syntax - `pinfo <pid>`
- Provides the following information about the process:
  - Process ID (PID)
  - Status 
  - Virtual Memory 
  - Path 

### history:

- Displays the most recently used commands (Only the past 20 commands are stored)
- Supports one extra argument - Number of  past commands to list

### jobs:

- Lists the jobs spawned by the shell in lexicographical order of process name
- Supports two flags - `-s` and `-r`

### fg, bg, sig:

- `fg` brings a background job to foreground
- `bg` resumes a stopped process by job number
- `sig` provides signals to the job

### repeat, replay:

- repeat x <command> runs the command x times
- replay -command <command> -interval x -period y runs the command after every x seconds, until y seconds have passed

### baywatch:

- Supports `-n` flag for now to print on a new line
- Supports three commands `interrupt`, `dirty`, `newborn`
- Quits ONLY when `q` key is pressed (signals are disabled while this command runs)

## Files Used:

| FILE NAME         | DESCRIPTION                                                  |
| ----------------- | ------------------------------------------------------------ |
| shell.h           | Contains macros, functions and other necessary elements to run the shell |
| main.c            | Contains the main function which runs the shell              |
| background.c      | Deals with the background processes                          |
| foreground.c      | Deals with the foreground processes                          |
| colors.c          | Just to add fancy colors to the shell                        |
| pinfo.c           | To display detailed information about a given process id     |
| signal_handling.c | SIGCHLD, SIGTSTP, SIGINT signal handling                     |
| ls.c              | Supports the ls command, which is used to list the contents of a directory |
| repeat.c          | To implement the repeat command, which repetitively performs a given process x number of times, where x is a parameter |
| pwd.c             | To get the absolute path of a current directory              |
| history.c         | Contains functions to display and store the previous commands (maximum 20 stored at a time) |
| history.txt       | Contains the information of the previous commands used (**DO NOT DELETE THIS**) |
| prompt.c          | To display the prompt after every command is executed        |
| cd.c              | Used to switch between directories                           |
| echo.c            | A shell equivalent of printf                                 |
| perms.c           | Used to list the permissions of a file (sub part of ls.c)    |
| execute.c         | To decode a given command by eliminating the whitespaces, and finally executing it. |
| baywatch.c        | Replicates the functionality of bash/watch along with an additional feature - exit on keypress "q" |
| redirect.c        | Support for redirection                                      |
| pipe.c            | Supports for piping                                          |
| jobs.c            | Displays the list of jobs in ascending order of job name     |
| fg.c              | Function to bring a job to foreground                        |
| bg.c              | Function to resume a stopped background process              |
| sig.c             | Provides a signal to a process                               |
| replay.c          | Function to run a given command for a given amount of time, after every x seconds (x is a parameter) |
| bgll.c            | Linked List functions to store the background processes      |

