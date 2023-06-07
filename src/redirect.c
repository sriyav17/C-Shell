#include "redirect.h"


int redirectFiles(char command1[])
{
    char temp[maxsize];
    strcpy(temp, command1);
       
    if(inprdct)
    {
        token = strtok(temp, "<");
        token = strtok(NULL, "<");
        if(outrdcta || outrdcto)
            token = strtok(token, ">");

        token = strtok(token, " \t \n");
        strcpy(temp, token);

        file1 = open(temp, O_RDONLY);
        if(file1 < 0)
        {
            perror("");
            return -1;
        }
        else
        {
            fflush(stdin);
            stdintemp = dup(0);
            dup2(file1, 0);
            close(file1);
        }
    }
    if(inprdct)
    {
        token = strtok(command1, "<");
        token = strtok(NULL, "<");
        strcpy(temp, token);
    }
    if(outrdcta)
    {
        fflush(stdout);
        token = strtok(temp, ">>");
        token = strtok(NULL, ">>");
        token = strtok(token, " \t \n");

        file2 = open(token, O_WRONLY|O_CREAT|O_APPEND, 0644);
        stdouttemp = dup(1);
        dup2(file2, 1); 
        close(file2);
    }
    else if(outrdcto)
    {
        fflush(stdout);
        token = strtok(temp, ">");
        token = strtok(NULL, ">");
        token = strtok(token, " \t \n");

        file2 = open(token, O_WRONLY|O_CREAT|O_TRUNC, 0644);
        stdouttemp = dup(1);
        dup2(file2, 1);
        close(file2);
    }
    return 1;
}   