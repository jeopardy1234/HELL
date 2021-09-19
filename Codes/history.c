#include "shell.h"

/*
For Storing:
Copy the contents of history.txt to temp_file.txt
While doing so, if the command is a repeated one, simply ignore it
Now, delete history.txt
Copy back temp_file.txt to history.txt
Incase temp_file.txt has 21 lines (cant have more than that) then start copying from first line
*/

void StoreHistory(char *s)
{
    char buffer[MAX_INP_SIZE];
    FILE *file = fopen(hisfile,"r");
    FILE *tempFile = fopen("temporary_file.txt","w");
    int cnt = 0;
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        if(strcmp(s,buffer) == 0)continue;
        fprintf(tempFile,"%s",buffer);
        cnt++;
    }
    fprintf(tempFile,"%s",s);
    fclose(tempFile);
    fclose(file);
    remove(hisfile);
    file = fopen(hisfile,"w");
    tempFile = fopen("temporary_file.txt","r");
    while(fgets(buffer, sizeof(buffer), tempFile) != NULL) {
        if(cnt > 19)
            {cnt--; continue;}
        fprintf(file,"%s",buffer);
        cnt--;
    }
    fclose(file);
    fclose(tempFile);
    remove("temporary_file.txt");
}

/*
For Storing:
Copy the contents of history.txt to temp_file.txt
While doing so, if the command is a repeated one, simply ignore it
Now, delete history.txt
Copy back temp_file.txt to history.txt
Incase temp_file.txt has 21 lines (cant have more than that) then start copying from first line
*/

void DisplayHistory(int argc, char**argv)
{
    FILE *file = fopen(hisfile,"r");
    if(argc > 2)
    {
        cprint("ERROR: ",RED);
        printf("Too many arguments!!\n");
        return ;
    }
    int num_lines = 10;
    if(argv[1] != NULL)
    {
        num_lines = toDecimal(argv[1]);
        if(num_lines == -1)
        {
            cprint("ERROR: ",RED);
            printf("Second argument is NaN\n");
            return ;
        }
    }
    int initial_lines = 0;
    char buffer[MAX_INP_SIZE];
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        initial_lines++;
    }
    rewind(file);
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        if(initial_lines <= num_lines)
        {
            fputs(buffer, stdout);
        }
        initial_lines--;
    }
    fclose(file);
}