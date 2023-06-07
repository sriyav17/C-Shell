#include "prompt.h"

void display()
{
    char temp[maxsize];
    getcwd(cwd, maxsize);
    if(strstr(cwd, homedir))
    {
        size_t len1 = strlen(cwd);
        size_t len2 = strlen(homedir);
        strcpy(temp, "~");                          
        memmove(temp+1, cwd + len2, len1-len2);
        temp[len1-len2+1] = '\0';
    }
    else
        strcpy(temp, cwd);

    printf(WHITE "<" CYAN "%s@%s" GREEN ":" YELLOW "%s", user, sysname, temp);
    if(t > 1)
        printf(WHITE "took %lds>", t);
    else
        printf(WHITE ">");
    prompt_done = 1;
}

void initdisplay()
{
    strcpy(prevdir, "");
    getcwd(homedir, maxsize);
    strcpy(cwd, homedir);
    gethostname(sysname, maxsize);
    getlogin_r(user, maxsize);
    display();
}