#include "jobs.h"               // need to fix for vim


int compare(const void* a, const void* b)
{
    struct background* x = (struct background*)a;
    struct background* y = (struct background*)b;
    return strcmp(x->bgname, y->bgname);
}


void jobs()
{
    int rflag = 0, sflag = 0;
    token = strtok(NULL, " ");
    while(token != NULL)
    {
        if(strcmp(token, "-rs") == 0 || strcmp(token, "-sr") == 0)
            rflag = sflag = 1;
        else if(strcmp(token, "-r") == 0)
            rflag = 1;
        else if(strcmp(token, "-s") == 0)
            sflag = 1;
        else    
        {
            printf("jobs: too many arguments\n");
            return;
        }
        token = strtok(NULL, " ");
    }
    if(rflag == 0 && sflag == 0)
        rflag = sflag = 1;

    qsort(bgprocesses, bgnum, sizeof(struct background), compare);

    char path[maxsize], status[maxsize];
    for(int i = 0; i < bgnum; i++)
    {
        sprintf(path, "/proc/%d/stat", bgprocesses[i].bgproc);
        FILE *f = fopen(path, "r");
        if(!f)
            continue;
        
        
        int j = 0;
        while(fscanf(f, "%s", status) == 1)
        {
            j++;
            if(j == 3)
                break;
        }   

        if(strcmp(status, "T") != 0 && rflag == 1)
            printf("[%d] Running %s [%d]\n", bgprocesses[i].bnum, bgprocesses[i].bgname, bgprocesses[i].bgproc);
        else if(strcmp(status, "T") == 0 && sflag == 1)
            printf("[%d] Stopped %s [%d]\n", bgprocesses[i].bnum, bgprocesses[i].bgname, bgprocesses[i].bgproc);   
    }
}