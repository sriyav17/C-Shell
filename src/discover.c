#include "discover.h"


int find_arguments(int* dflag, int* fflag, int* num_of_dir, char directory[], char filename[])
{
    token = strtok(NULL, " ");
    int count = 0;

    while(token)
    {
        if(strcmp(token, "-d") == 0)
            *dflag = 1;
        else if(strcmp(token, "-f") == 0)
            *fflag = 1;
        else if(strcmp(token, "-df") == 0)
            *dflag = *fflag = 1;
        else if(strcmp(token, "-fd") == 0)
            *dflag = *fflag = 1;
        else if(token[0] == '\"')
        {   
            char temp[maxsize];
            strcpy(temp, token+1);
            temp[strlen(temp)-1] = '\0';
            strcpy(filename, temp);
            count++;
        }
        else
        {
            strcpy(directory, token);
            *num_of_dir = 1;
        }
        token = strtok(NULL, " ");
    }
    if(*dflag == 0 && *fflag == 0)
        *dflag = *fflag = 1;

    return count;
}


int search(char temp[], char path[], int* dflag, int* fflag, int check, char filename[])
{
    char prev[maxsize], prevtemp[maxsize], curr[maxsize];
    int retval = 0;
    getcwd(prev, maxsize);

    int ret = chdir(path);
    if(ret == -1)
        return -1;

    getcwd(curr, maxsize);

    if(check == 0 && *dflag == 1)
        printf("%s\n", temp);

    strcpy(prevtemp, temp);
    int number;
    struct dirent** lsnames;
    number = scandir(path, &lsnames, NULL, alphasort);
    if(number == -1)
    {
        perror("sirya: ls");
        return 1;
    }

    for(int i = 0; i < number; i++)
    {
        char name[maxsize];
        if(lsnames[i]->d_name[0] == '.')
        {
            free(lsnames[i]);
            continue;
        }
        DIR* temp2 = opendir(lsnames[i]->d_name);
        if(temp2 == NULL)
        {
            strcpy(name, temp);
            strcat(name, "/");
            strcat(name, lsnames[i]->d_name);
            if(check != 0)
            {
                if(strcmp(lsnames[i]->d_name, filename) == 0)
                {
                    if(*fflag == 1)
                        printf("%s\n", name);
                    retval = 1;
                }
            }
            else
            {
                if(*fflag == 1)
                    printf("%s\n", name);
            }
        }
        else
        {
            strcat(temp, "/");
            strcat(temp, lsnames[i]->d_name);
            strcat(path, "/");
            strcat(path, lsnames[i]->d_name);
            if(check == 1 && *dflag == 1)
            {
                if(strcmp(lsnames[i]->d_name, filename) == 0)
                    printf("%s\n", temp);
            }
            retval = search(temp, path, dflag, fflag, check, filename);
            strcpy(temp, prevtemp); 
            strcpy(path, curr);
        }
        closedir(temp2);    
        free(lsnames[i]);  
    }   

    chdir(prev); 
    strcpy(temp, prevtemp); 
    return retval;
}


void discover()
{
    int dflag, fflag;
    dflag = fflag = 0;

    char directory[maxsize], filename[maxsize];
    int num_of_dir = 0;
    int num_of_files = find_arguments(&dflag, &fflag, &num_of_dir, directory, filename);
    
    char temp[maxsize], path[maxsize];
    if(num_of_dir == 0)
    {
        strcpy(temp, ".");
        strcpy(path, cwd);
    }
    else
    {
        strcpy(temp, directory);
        if(directory[0] == '~')
        {
            char temp2[maxsize];
            strcpy(temp2, directory+1);
            strcpy(directory, homedir);
            strcat(directory, temp2);
        }
        int ret = chdir(directory);
        if(ret == -1)
        {
            perror("sirya: discover");
            return;
        }
        getcwd(path, maxsize);
        chdir(cwd);  
    }

    int check = 0, retval;
    if(num_of_files == 0)
    {
        retval = search(temp, path, &dflag, &fflag, check, filename);
    }
    else
    {
        check = 1;
        retval = search(temp, path, &dflag, &fflag, check, filename);   
    }

}