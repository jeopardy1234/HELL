#include "shell.h"

void StoreHistory(char *s, FILE *file)
{
    FILE *tempFile = fopen("temporary_file.txt","r");
    char buffer[MAX_INP_SIZE];
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
         if(strcmp(s,buffer) == 0)continue;
         fprintf(tempFile,"%s",buffer);
     }
    //  while(fgets(buffer, sizeof(buffer), tempFile) != NULL) {
    //      //if(strcmp(s,buffer) == 0)continue;
    //      fprintf(history_file,"%s",buffer);
    //  }
    //  fprintf(history_file,"%s",s);
    //  fclose(tempFile);
    //  fclose(history_file);
    //  remove("history.txt");
    //  rename("temporary_file.txt","history.txt");
     //history_file = fopen("history.txt","r+");
}

void DisplayHistory(int argc, char**argv, FILE* file)
{
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
    char buffer[MAX_INP_SIZE];
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
         num_lines--;
         if(num_lines < 0)break;
         fputs(buffer, stdout);
     }
    rewind(history_file);

}