#include "fg.h"

void fg()
{
    token = strtok(NULL, " ");
    if (token == NULL)
    {
        printf("too few arguments\n");
        return;
    }
    int procnum = atoi(token);

    token = strtok(NULL, " ");
    if (token != NULL)
    {
        printf("too many arguments\n");
        return;
    }
    if (procnum < 1)
    {
        printf("invalid argument\n");
        return;
    }

    for (int i = 0; i < bgnum; i++)
    {
        if (bgprocesses[i].bnum == procnum)
        {
            int status;
            setpgid(bgprocesses[i].bgproc, getpgid(0));

            // signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);

            tcsetpgrp(0, bgprocesses[i].bgproc);

            if (kill(bgprocesses[i].bgproc, SIGCONT) < 0)
                printf("fg failed");
            
            waitpid(bgprocesses[i].bgproc, &status, WUNTRACED);

            tcsetpgrp(0, getpgid(0));

            // signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);

            // if (WIFSTOPPED(status))
            //     return 0;

            return;
        }
    }

    printf("job not found\n");
}