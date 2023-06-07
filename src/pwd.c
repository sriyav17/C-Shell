#include "pwd.h"

void pwd()
{
    getcwd(cwd, maxsize);
    printf("%s\n", cwd);
}