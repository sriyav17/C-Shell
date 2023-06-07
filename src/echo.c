#include "echo.h"

void echo()
{
    token = strtok(NULL, " ");
    char temp = '\n';
    while(token)
    {
        if(strchr(token, temp))
        {
            token[strlen(token)-1] = '\0';
        }
        printf("%s ", token);
        token = strtok(NULL, " ");
    }
    printf("\n");
}