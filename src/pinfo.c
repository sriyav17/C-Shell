#include "pinfo.h"

void pinfo()
{
    pid_t pid;
    
    token = strtok(NULL, "");
    if(token)
    {
        if(strchr(token, '\n'))
            token[strlen(token)-1] = '\0';
    }
    if(!token || strcmp(token, "") == 0)
        pid = getpid();
    else
        pid = atoi(token);

    char filename[100];
    sprintf(filename, "/proc/%d/stat", pid);

    FILE* file = fopen(filename, "r");
    if(!file)
    {
        perror("sirya: pinfo");
        return;
    }
    
    char temp[maxsize], status[maxsize], pgrp[maxsize], tgrp[maxsize], memory[maxsize];
    int i = 1;
    while(fscanf(file, "%s", temp) == 1)
    {
        if(i == 3)
            strcpy(status, temp);
        else if(i == 5)
            strcpy(pgrp, temp);
        else if(i == 8)
            strcpy(tgrp, temp);
        else if(i == 23)
            strcpy(memory, temp);
        i++;
    }

    fclose(file);
    
    sprintf(filename, "/proc/%d/exe", pid);
    char path[100];
    readlink(filename, path, maxsize);
    if(strstr(path, homedir))
    {
        size_t len1 = strlen(path);
        size_t len2 = strlen(homedir);
        strcpy(path, "~");                          
        memmove(path+1, path + len2, len1-len2);
        path[len1-len2+1] = '\0';
    }

    if(strcmp(pgrp, tgrp) == 0)
        strcat(status, "+");
    
    printf("pid : %d\n", pid);
    printf("process status : %s\n", status);
    printf("memory : %s\n", memory);
    printf("executable path : %s\n", path);
}