#include "sighandler.h"


void sighan_c()
{
    if(isfg)
    {
        printf("\n");
        fflush(stdout);
    }
    isfg = 0;
}

void sighan_z()
{
    if(isfg)
    {
        kill(fgproc, 20);
        bgnum++;
        bgprocesses[bgnum-1].bgproc = fgproc;
        bgprocesses[bgnum-1].bgname = (char*)malloc(strlen(fgname));
        bgprocesses[bgnum-1].bnum = bgnum;
        strcpy(bgprocesses[bgnum-1].bgname, fgname);
    }
    isfg = 0;
}