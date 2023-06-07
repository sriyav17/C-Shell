#include "bg.h"

void bg()
{
    token = strtok(NULL, " ");
    if(token == NULL)
    {
        printf("too few arguments\n");
        return;
    }
    int procnum = atoi(token);

    token = strtok(NULL, " ");
    if(token != NULL)
    {
        printf("too many arguments\n");
        return;
    }
    if(procnum < 1)
    {
        printf("invalid argument\n");
        return;
    }

    for(int i = 0; i < bgnum; i++)
    {
        if(bgprocesses[i].bnum == procnum)
        {
            int temp = kill(bgprocesses[i].bgproc, SIGCONT);
            if(temp < 0)
                printf("bg failed");
            return;
        }
    }

    printf("job not found\n");
}