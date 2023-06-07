#include "ls.h"

int sort(char directories[][maxsize], int num_of_dir)
{
    while(1)
    {
        int swapcount = 0;
        for(int i = 0; i < num_of_dir-1; i++)
        {
            if(strcasecmp(directories[i], directories[i+1]) > 0)
            {
                char temp[maxsize];
                strcpy(temp, directories[i]);
                strcpy(directories[i], directories[i+1]);
                strcpy(directories[i+1], temp);
                swapcount++;
            }
        }
        if(swapcount == 0)
            break;
    }
}

int alphasort(const struct dirent **a, const struct dirent **b) 
{
    char x[100], y[100];
    // aname = (*a)->d_name; 
    // bname = (*b)->d_name;
    
    if((*a)->d_name[0] == '.')
        strcpy(x, (*a)->d_name + 1);
    else
        strcpy(x, (*a)->d_name);
    if((*b)->d_name[0] == '.')
        strcpy(y, (*b)->d_name + 1);
    else
        strcpy(y, (*b)->d_name);

    return strcasecmp(x, y);
}  


void perms(struct stat filestat)
{
    printf((S_ISDIR(filestat.st_mode)) ? WHITE "d" : WHITE "-");
    printf((filestat.st_mode & S_IRUSR) ? "r" : "-");
    printf((filestat.st_mode & S_IWUSR) ? "w" : "-");
    printf((filestat.st_mode & S_IXUSR) ? "x" : "-");
    printf((filestat.st_mode & S_IRGRP) ? "r" : "-");
    printf((filestat.st_mode & S_IWGRP) ? "w" : "-");
    printf((filestat.st_mode & S_IXGRP) ? "x" : "-");
    printf((filestat.st_mode & S_IROTH) ? "r" : "-");
    printf((filestat.st_mode & S_IWOTH) ? "w" : "-");
    printf((filestat.st_mode & S_IXOTH) ? "x" : "-");
}


int find_flags_and_dir(int* lflag, int* aflag, int* num_of_dir, char tempdir[][maxsize])
{
    token = strtok(NULL, " ");
    int count = 0;
    int index = 0;
    while(token)
    {
        if(strchr(token, '\n'))
            token[strlen(token)-1] = '\0';
        
        if(strcmp(token, "-l") == 0)
        {
            *lflag = 1;
            count++;
        }
        else if(strcmp(token, "-a") == 0)
        {
            *aflag = 1;
            count++;
        }
        else if(strcmp(token, "-al") == 0 || strcmp(token, "-la") == 0)
        {
            *lflag = *aflag = 1;
            count++;
        }
        else
        {   
            (*num_of_dir)++;
            if(token[0] == '~')
            {
                strcpy(tempdir[index], homedir);
                if(strlen(token) > 1)
                {
                    size_t len = strlen(token) - 1;
                    memmove(token, token+1, len);
                    token[len] = '\0';
                    strcat(tempdir[index], token);
                }
                index++;
            }
            else
            {
                strcpy(tempdir[index], token);
                index++;
            }
        }
        token = strtok(NULL, " ");
    }
    return count;
}

void ls()
{

    int lflag, aflag;
    lflag = aflag = 0;

    int num_of_dir = 0;
    char directories[maxsize][maxsize];
    int num_of_flags = find_flags_and_dir(&lflag, &aflag, &num_of_dir, directories);
    int color;

    if(num_of_dir == 0)
    {
        int number;
        struct dirent** lsnames;
        number = scandir(cwd, &lsnames, NULL, alphasort);
        if(number == -1)
        {
            perror("sirya: ls");
            return;
        }
        
        for(int i = 0; i < number; i++)
        {
            if(aflag == 0 && lsnames[i]->d_name[0] == '.')
            {
                free(lsnames[i]);
                continue;
            }

            struct stat filestat;
            struct passwd* owner;
            struct group* group;
            char date[maxsize];
            stat(lsnames[i]->d_name, &filestat);
            owner = getpwuid(filestat.st_uid);
            group = getgrgid(filestat.st_gid);
            strftime(date, 35, "%b %d %H:%M", localtime(&filestat.st_mtime));

            if(S_ISDIR(filestat.st_mode))
                color = 0;
            else
            {
                if(filestat.st_mode & S_IXOTH)
                    color = 2;
                else
                    color = 1;
            }

            if(lflag == 1)
            {
                perms(filestat);
                printf(WHITE " %2ld %s %s %6ld %s ", filestat.st_nlink, owner->pw_name, group->gr_name, filestat.st_size, date);            
                if(color == 0)
                    printf(CYAN "%s\n", lsnames[i]->d_name);
                else if(color == 1)
                    printf(WHITE "%s\n", lsnames[i]->d_name);
                else
                    printf(GREEN "%s\n", lsnames[i]->d_name);
            }
            else
            {
                if(color == 0)
                    printf(CYAN "%s\n", lsnames[i]->d_name);
                else if(color == 1)
                    printf(WHITE "%s\n", lsnames[i]->d_name);
                else
                    printf(GREEN "%s\n", lsnames[i]->d_name);
            }

            free(lsnames[i]);
        }
        free(lsnames);
        return;
    }  

    sort(directories, num_of_dir); 
    for(int i = 0; i < num_of_dir; i++)
    {   
        DIR* dir2 = opendir(directories[i]);
        if(!dir2)
        {
            if(access(directories[i], F_OK) != 0)                                   
            {
                perror("sirya: ls");    
            }
            else
            {   
                int number;
                struct stat filestat;
                struct passwd* owner;
                struct group* group;
                char date[maxsize];
                stat(directories[i], &filestat);
                owner = getpwuid(filestat.st_uid);
                group = getgrgid(filestat.st_gid);

                strftime(date, 35, "%b %d %H:%M", localtime(&filestat.st_mtime));

                if(S_ISDIR(filestat.st_mode))
                    color = 0;
                else
                {
                    if(filestat.st_mode & S_IXOTH)
                        color = 2;
                    else
                        color = 1;
                }

                if(lflag == 1)
                {
                    perms(filestat);
                    printf(WHITE " %2ld %s %s %6ld %s ", filestat.st_nlink, owner->pw_name, group->gr_name, filestat.st_size, date);
                    
                    if(color == 0)
                        printf(CYAN "%s\n", directories[i]);
                    else if(color == 1)
                        printf(WHITE "%s\n", directories[i]);
                    else
                        printf(GREEN "%s\n", directories[i]);
                }
                else
                    if(color == 0)
                        printf(CYAN "%s\n", directories[i]);
                    else if(color == 1)
                        printf(WHITE "%s\n", directories[i]);
                    else
                        printf(GREEN "%s\n", directories[i]);
            }
            continue;
        }

        char path[maxsize];
        int ret = chdir(directories[i]);
        if(ret == -1)
            perror("sirya: ls");
        getcwd(path, maxsize);

        if(num_of_dir > 1)
        {
            printf(WHITE "%s:\n", directories[i]);
        }
        
        int number;
        struct dirent** lsnames;
        number = scandir(path, &lsnames, NULL, alphasort);
        if(number == -1)
        {
            perror("siyra: ls");
            return;
        }
        
        for(int i = 0; i < number; i++)
        {
            if(aflag == 0 && lsnames[i]->d_name[0] == '.')
            {
                free(lsnames[i]);
                continue;
            }

            struct stat filestat;
            struct passwd* owner;
            struct group* group;
            char date[maxsize];
            stat(lsnames[i]->d_name, &filestat);
            owner = getpwuid(filestat.st_uid);
            group = getgrgid(filestat.st_gid);

            strftime(date, 35, "%b %d %H:%M", localtime(&filestat.st_mtime));

            if(S_ISDIR(filestat.st_mode))
                color = 0;
            else
            {
                if((filestat.st_mode & S_IXOTH) == 1)
                    color = 2;
                else
                    color = 1;
            }

            if(lflag == 1)
            {
                perms(filestat);
                printf(WHITE " %2ld %s %s %6ld %s ", filestat.st_nlink, owner->pw_name, group->gr_name, filestat.st_size, date);            
                if(color == 0)
                    printf(CYAN "%s\n", lsnames[i]->d_name);
                else if(color == 1)
                    printf(WHITE "%s\n", lsnames[i]->d_name);
                else
                    printf(GREEN "%s\n", lsnames[i]->d_name);
            }
            else
            {
                if(color == 0)
                    printf(CYAN "%s\n", lsnames[i]->d_name);
                else if(color == 1)
                    printf(WHITE "%s\n", lsnames[i]->d_name);
                else
                    printf(GREEN "%s\n", lsnames[i]->d_name);
            }
            free(lsnames[i]);
        }
        free(lsnames);
        chdir(cwd);
        closedir(dir2);

        if(i != num_of_dir-1)
            printf("\n");   
    }
}