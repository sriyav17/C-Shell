#include "tab.h"

void tab(int *index)
{
    char buffer[maxsize], find[maxsize];
    char path[maxsize];
    if (buf[0] == '\0')
    {
        getcwd(path, maxsize);
        int number;
        struct dirent **tabnames;
        number = scandir(path, &tabnames, NULL, NULL);
        for (int i = 0; i < number; i++)
        {
            if (tabnames[i]->d_name[0] == '.')
            {
                free(tabnames[i]);
                continue;
            }

            struct stat filestat;
            stat(tabnames[i]->d_name, &filestat);

            printf("\n");
            for (int j = 0; j < strlen(tabnames[i]->d_name); j++)
                printf("%c", tabnames[i]->d_name[j]);
            
            if (S_ISDIR(filestat.st_mode))
                printf("/");

            free(tabnames[i]);
        }
        printf("\n");
        display();
        return;
    }

    strcpy(buffer, buf);
    token = strtok(buffer, " ");
    memset(find, '\0', maxsize);
    strcpy(find, token);
    find[strlen(token)-1] = '\0';
    while (token)
    {
        memset(find, '\0', maxsize);
        strcpy(find, token);
        find[strlen(token) - 1] = '\0';
        token = strtok(NULL, " ");
    }

    path[0] = '\0';
    for (int i = 0; i < strlen(find); i++)
    {
        if (find[i] == '/')
        {
            strncpy(path, find, i);
            strcpy(find, find + i + 1);
            find[strlen(find+i+1)-1] = '\0';
            path[i + 1] = '\0';
        }
    }
    if (path[0] != '\0')
    {
        if (chdir(path) < 0)
            perror("");
    }

    getcwd(path, maxsize);

    // DIR* dir = opendir(path);
    int number;
    struct dirent **tabnames;

    // if(dir)
    // {
    number = scandir(path, &tabnames, NULL, NULL);
    int count = 0;
    char common[maxsize];
    common[0] = '\0';
    char *names[maxsize];
    for (int i = 0; i < number; i++)
    {
        if (tabnames[i]->d_name[0] == '.')
        {
            free(tabnames[i]);
            continue;
        }

        if (strlen(find) <= strlen(tabnames[i]->d_name) && strncmp(tabnames[i]->d_name, find, strlen(find) - 1) == 0)
        {
            names[count++] = (char *)malloc(strlen(tabnames[i]->d_name));
            strcpy(names[count - 1], tabnames[i]->d_name);
            if (common[0] == '\0')
                strcpy(common, tabnames[i]->d_name);
        }

        free(tabnames[i]);
    }

    if (count == 1)
    {
        struct stat filestat;
        stat(names[0], &filestat);

        for (int j = strlen(find); j < strlen(names[0]); j++)
        {
            printf("%c", names[0][j]);
            buf[*index++] = names[0][j];
        }
        if (S_ISDIR(filestat.st_mode))
        {
            printf("/");
            buf[*index++] = '/';
        }
        else
        {
            printf(" ");
            buf[*index++] = ' ';
        }
    }
    else if (count > 1)
    {
        for (int i = 0; i < count; i++)
        {
            struct stat filestat;
            stat(names[i], &filestat);

            printf("\n");
            for (int j = 0; j < strlen(names[i]); j++)
            {
                printf("%c", names[i][j]);
                if (j < strlen(common) && names[i][j] != common[j])
                    common[j] = '\0';
            }
            if (S_ISDIR(filestat.st_mode))
                printf("/");
        }
        for (int i = strlen(find); i < strlen(common); i++)
            buf[(*index)++] = common[i];
        buf[*index] = '\0';
        printf("\n");
        display();
        printf("%s", buf);
    }
    chdir(cwd);
    // }
}