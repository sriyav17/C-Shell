#include "sig.h"            // fix  sig 1 9

void sig()
{
    token = strtok(NULL, " ");
    if(token == NULL)
    {
        printf("invalid command\n");
        return;
    }
    int procnum = atoi(token);
    
    token = strtok(NULL, " ");
    if(token == NULL)
    {
        printf("inavlid command\n");
        return;
    }
    int signum = atoi(token);
    if(procnum < 1)
    {
        printf("invalid process number\n");
        return;
    }

    for(int i = 0; i < bgnum; i++)
    {
        if(bgprocesses[i].bnum == procnum)
        {
            int temp = kill(bgprocesses[i].bgproc, signum);
            if(temp < 0)
                printf("invalid signal number\n");
            
            return;
        }
    }

    printf("job not found\n");
    return;
}