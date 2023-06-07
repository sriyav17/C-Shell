#include "headers.h"
#include "prompt.h"
#include "input.h"
#include "bgfg.h"
#include "sighandler.h"

char* buf;
char* user;
char* sysname;
char* cwd;
char* homedir;
char* prevdir;
int prompt_done;
char* token;
char** command;
clock_t t;
int bgnum;
struct background bgprocesses[maxsize];
int bgnum2;
int prevbgnum2;
char* exitstring[maxsize];
int inprdct;
int outrdcto;
int outrdcta;
char inpfilename[maxsize];
char outfilename[maxsize];
int file1;
int file2;
int stdouttemp;
int stdintemp;
int isfg;
pid_t fgproc;
char fgname[maxsize];


int main()
{
    user = (char*)malloc(maxsize);
    sysname = (char*)malloc(maxsize);
    cwd = (char*)malloc(maxsize);
    homedir = (char*)malloc(maxsize);
    prevdir = (char*)malloc(maxsize);
    bgnum = bgnum2 = prevbgnum2 = 0;
    isfg = 0;
    fgproc = INT_MIN;
    initdisplay();

    signal(SIGCHLD, bg_exit);
    signal(SIGINT, sighan_c);
    signal(SIGTSTP, sighan_z);
        
    while(1)
    {
        for(int i = prevbgnum2; i < bgnum2; i++)
        {
            printf("%s\n", exitstring[i]);
            prevbgnum2 = bgnum2;
        }

        if(prompt_done)
        {
            input();
            prompt_done = 0;
        }
        else
            display();
    }
}