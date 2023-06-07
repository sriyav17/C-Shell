#include "history.h"


void add_history()
{
    char path[maxsize];
    // strcpy(path, "~");
    strcpy(path, homedir);
    strcat(path, "/");
    strcat(path, "hist.txt");
    FILE* f = fopen(path, "a");
    fclose(f);
    f = fopen(path, "r+");
    char* lines[20];
    char* temp;
    size_t len = 0;

    int i = 0;
    for(i = 0; i < 20; i++)
    {
        if(getline(&temp, &len, f) == -1)
        {
            break;
        }
        temp[strlen(temp)-1] = '\0';
        lines[i] = (char*)malloc(strlen(temp));
        strcpy(lines[i], temp);
    }
    
    len = strlen(lines[i-1]);
    len *= -1;

    if(strchr(buf, '\n'))
        buf[strlen(buf)-1] = '\0';
    
    if(strcmp(buf, lines[i-1]) != 0)
    {
        if(i == 0)
        {
            fprintf(f, "%s\n", buf);
        }
        else if(i < 20)
        {
            fseek(f, 0, SEEK_END);
            fprintf(f, "%s\n", buf);
        }
        else if(i >= 20) 
        {
            fseek(f, 0, SEEK_SET);
            for(int j = 0; j < 19; j++)
            {
                for(int k = 0; k < strlen(lines[j]); k++)
                {
                    fprintf(f, "\0");
                }
                fprintf(f, "%s\n", lines[j+1]);
            }
            fprintf(f, "%s\n", buf);
        }
    }
    fclose(f);
}

void print_history()
{
    char path[maxsize];
    // strcpy(path, "~");
    strcpy(path, homedir);
    strcat(path, "/");
    strcat(path, "hist.txt");
    FILE* f = fopen(path, "r");
    char* lines[20];
    char *temp;
    size_t len = 0;

    int i = 0;
    for(i = 0; i < 20; i++)
    {
        if(getline(&temp, &len, f) == -1)
        {
            break;
        }
        temp[strlen(temp)-1] = '\0';
        lines[i] = (char*)malloc(strlen(temp));
        strcpy(lines[i], temp);
    }

    int k = 0;
    if(i <= 10)
        k = 0;
    else
        k = i-10;
    for(int j = k; j < i; j++)
    {
        printf("%s\n", lines[j]);
    }
    fclose(f);
}