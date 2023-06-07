#include "cd.h"


int cd()
{
    token = strtok(NULL, " ");
    char* check = strtok(NULL, " ");
    if(check && strcmp(check, "\n") != 0)
    {
        printf("sirya: cd: too many arguments\n");
        return -1;
    }
    int newline = '\n';
    if(token != NULL && strchr(token, newline))
        token[strlen(token)-1] = '\0';
    if(!token || strlen(token) == 0)
    {
        strcpy(prevdir, cwd);
        int ret = chdir(homedir);
        if(ret == -1)
        {
            perror("sirya: cd");
            return -1;
        }
    }
    else if(token[0] == '.' && token[1] == '.')
    {
        char* pardir;
        char temp[maxsize];
        strcpy(temp, cwd);
        pardir = dirname(cwd);
        if(strlen(token) > 2)
        {
            size_t len = strlen(token) - 2;
            memmove(token, token+2, len);
            token[len] = '\0';
            strcat(pardir, token);
        }
        int ret = chdir(pardir);
        if(ret == -1)
        {
            perror("sirya: cd");
            return -1;
        }
        else
            strcpy(prevdir, temp);
    }
    else if(token[0] == '.')
    {
        int ret = chdir(token);
        if(ret == -1)
        {
            perror("sirya: cd");
            return -1;
        }
        else
            strcpy(prevdir, cwd);
    }
    else if(token[0] == '-')
    {
        if(strlen(token) > 1)
        {
            printf("sirya: cd: invalid option\n");
            return -1;
        }
        if(strcmp(prevdir, "") == 0)
        {
            printf("sirya: cd: OLDPWD not set\n");
            return -1;
        }
        else
        {
            int ret = chdir(prevdir);
            if(ret == -1)
            {
                perror("sirya: cd");
                return -1;
            }
            else
            {
                printf("%s\n", prevdir);
                char temp[maxsize];
                strcpy(temp, prevdir);
                strcpy(prevdir, cwd);
                strcpy(cwd, temp);
            }
        }
    }
    else if(token[0] == '~')
    {
        char temp[maxsize];
        strcpy(temp, homedir);
        if(strlen(token) > 1)
        {
            size_t len = strlen(token) - 1;
            memmove(token, token+1, len);
            token[len] = '\0';
            strcat(temp, token);
        }
        int ret = chdir(temp);
        if(ret == -1)
        {
            perror("sirya: cd");
            return -1;
        }
        else
            strcpy(prevdir, cwd);
    }
    else if(token[0] == '/')
    {
        int ret = chdir(token);
        if(ret == -1)
        {
            perror("sirya: cd");
            return -1;
        }
        else
            strcpy(prevdir, cwd);
    }
    else
    {
        char temp[maxsize];
        strcpy(temp, cwd);
        size_t len = strlen(temp);
        temp[len] = '/';
        temp[len+1] = '\0';
        strcat(temp, token);
        int ret = chdir(temp);
        if(ret == -1)
        {
            perror("sirya: cd");
            return -1;
        }
        else
            strcpy(prevdir, cwd);
    }
    return 1;
}