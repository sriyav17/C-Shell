#ifndef GLO_H
#define GLO_H

struct background {
    int bgproc;
    char* bgname;
    int bnum;
};

extern char* buf;
extern char* user;
extern char* sysname;
extern char* cwd;
extern char* homedir;
extern char* prevdir;
extern int prompt_done;
extern char* token;
extern char** command;
extern clock_t t;
extern int bgnum;
extern struct background bgprocesses[maxsize];
extern int bgnum2;
extern int prevbgnum2;
extern char* exitstring[maxsize];
extern int inprdct;
extern int outrdcto;
extern int outrdcta;
extern char inpfilename[maxsize];
extern char outfilename[maxsize];
extern int file1;
extern int file2;
extern int stdouttemp;
extern int stdintemp;
extern int isfg;
extern pid_t fgproc;
extern char fgname[maxsize];

#endif