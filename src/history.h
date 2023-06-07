#ifndef HIS_H
#define HIS_H

#include "headers.h"
#include "global.h"

extern char* buf;
extern char* user;
extern char* sysname;
extern char* cwd;
extern char* homedir;
extern char* prevdir;
extern int prompt_done;
extern char* token;
extern char** command;
extern int bgnum;
extern int inprdct;
extern int outrdcto;
extern int outrdcta;

void add_history();
void print_history();

#endif