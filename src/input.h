#ifndef INP_H
#define INP_H

#include "headers.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "ls.h"
#include "pinfo.h"
#include "history.h"
#include "discover.h"
#include "bgfg.h"
#include "global.h"
#include "redirect.h"
#include "pipe.h"
#include "jobs.h"
#include "sig.h"
#include "bg.h"
#include "fg.h"
#include "tab.h"


void and_proc(char command[]);
void findCommand(char command1[], char tempcom[]);
int input();


#endif