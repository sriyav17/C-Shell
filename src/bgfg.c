#include "bgfg.h"

void bgfg_proc(char command1[], int flag)
{
    char *ptr1, *ptr2;
    char *arguments[maxsize];
    token = strtok_r(command1, " ", &ptr1);
    if (token == NULL)
        return;

    if (strchr(token, '\n'))
        token[strlen(token) - 1] = '\0';

    if (strcmp(token, "") == 0)
        return;

    int count = 0;
    while (token)
    {
        char temp[maxsize];
        if (strchr(token, '\n'))
            token[strlen(token) - 1] = '\0';

        if (strchr(token, '<'))
        {
            if (strcmp(token, "<") == 0)
            {
                token = strtok_r(NULL, " ", &ptr1);
                continue;
            }

            if (token[0] == '<')
            {
                strcpy(token, token + 1);
            }
            else if (token[strlen(token) - 1] == '<')
                token[strlen(token) - 1] = '\0';
            else
            {
                strcpy(temp, token);
                token = strtok(temp, "<");
                arguments[count] = (char *)malloc(maxsize);

                strcpy(arguments[count++], token);
                token = strtok_r(NULL, " ", &ptr1);
            }
        }
        if (strchr(token, '>'))
        {
            if (token[0] == '>')
                break;

            strcpy(temp, token);
            token = strtok(token, ">");
        }

        arguments[count] = (char *)malloc(maxsize);

        strcpy(arguments[count++], token);
        token = strtok_r(NULL, " ", &ptr1);
    }
    
    pid_t ret = fork();
    if(flag == 0)
    {
        isfg = 1;
        fgproc = ret;
        strcpy(fgname, arguments[0]);
    }
    int status;

    if (ret == 0)
    {
        if (flag == 1)
            setpgid(0, 0);
        int ret2 = execvp(arguments[0], arguments);
        if(ret2 == -1)
            printf("command not found\n");
    }   
    else
    {
        if (flag == 0)
        {
            waitpid(ret, &status, WSTOPPED); // foreground
            isfg = 0;
        }
        else
        {
            waitpid(ret, &status, WNOHANG); // background
            printf("[%d] %d\n", bgnum++, ret);
            bgprocesses[bgnum-1].bgproc = ret;
            bgprocesses[bgnum-1].bgname = (char*)malloc(strlen(arguments[0]));
            bgprocesses[bgnum-1].bnum = bgnum;
            strcpy(bgprocesses[bgnum-1].bgname, arguments[0]);
        }
    }

    for (int i = 0; i < count; i++)
        free(arguments[i]);
}

void bg_exit()
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    char temp[maxsize];

    if (pid > 0)
    {
        int i = 0;
        while (bgprocesses[i].bgproc != pid)
        {
            i++;
        }

        if (WIFSTOPPED(status))
            return;

        if (WIFEXITED(status))
        {
            sprintf(temp, "%s with PID = %d exited %s", bgprocesses[i].bgname, bgprocesses[i].bgproc, "normally");
            exitstring[bgnum2] = (char *)malloc(strlen(temp));
            strcpy(exitstring[bgnum2++], temp);
        }
        else
        {
            sprintf(temp, "%s with PID = %d exited %s", bgprocesses[i].bgname, bgprocesses[i].bgproc, "abnormally");
            exitstring[bgnum2] = (char *)malloc(strlen(temp));
            strcpy(exitstring[bgnum2++], temp);
        }
    }
}
