# (S)Hell

## To Run:

> make
>
> ./a.out

## Assumptions:

- Number of semicolon separated inputs is max 512 characters
- Hostname size if max 512 characters
- Max size of input is not more than 2048 characters at once
- history.txt file won't be deleted while running the shell

## Files Used:

| FILE NAME         | DESCRIPTION                                                  |
| ----------------- | ------------------------------------------------------------ |
| shell.h           | Contains macros, functions and other necessary elements to run the shell |
| main.c            | Contains the main function which runs the shell              |
| background.c      | Deals with the background processes                          |
| foreground.c      | Deals with the foreground processes                          |
| colors.c          | Just to add fancy colors to the shell                        |
| pinfo.c           | To display detailed information about a given process id     |
| signal_handling.c | For now, just to deal with SIGCHLD signal for reaping the background process, and displaying it's info |
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

