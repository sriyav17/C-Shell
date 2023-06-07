#include "pipe.h"
#include "input.h"

int pipeCommand(char command1[])
{
    char *splitcommands[maxsize];
    int numofpipes = -1;
    token = strtok(command1, "|");
    int count = 0;
    while (token)
    {
        numofpipes++;
        splitcommands[count] = (char *)malloc(strlen(token));
        strcpy(splitcommands[count++], token);
        token = strtok(NULL, "|");
    }
    if (numofpipes == 0)
        return 0;

    int fd[numofpipes][2];

    for (int i = 0; i < numofpipes; i++)
    {
        if (pipe(fd[i]) < 0)
            perror("");
    }

    for (int i = 0; i < count; i++)
    {
        pid_t ret = fork();
        if (ret == 0)
        {
            if (i != 0)
            {
                close(fd[i - 1][1]);
                dup2(fd[i - 1][0], 0);
                close(fd[i - 1][0]);
            }
            if (i != count - 1)
                dup2(fd[i][1], 1);

            char tempcom[maxsize];
            strcpy(tempcom, splitcommands[i]);

            if(strchr(splitcommands[i], '<'))
                inprdct = 1;
            if(strstr(splitcommands[i], ">>"))
                outrdcta = 1;
            else if(strchr(splitcommands[i], '>'))
                outrdcto = 1;
            if(inprdct || outrdcta || outrdcto)
                redirectFiles(splitcommands[i]);

                
            findCommand(splitcommands[i], tempcom);

            exit(0);
        }
        else
        {
            dup2(STDIN_FILENO, 0);
            dup2(STDOUT_FILENO, 1);
        }
    }

    close(fd[numofpipes - 1][0]);
    close(fd[numofpipes - 1][1]);

    for (int i = 0; i < count; ++i)
    {
        wait(NULL);
    }
    dup2(STDOUT_FILENO, 1);
    dup2(STDIN_FILENO, 0);

    return 1;
}