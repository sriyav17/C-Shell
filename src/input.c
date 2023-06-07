#include "input.h"
 
void and_proc(char command1[])
{
    int check = 0;
    int len = strlen(command1);
    if(command1[len-1] == '\n')
        command1[len-1] = '\0';
    else if(command1[strlen(command1)-1] == '&')
        check = 1;

    token = strtok(command1, "&");
    int comnum = 0;
    char* commands[maxsize];
    while(token)
    {
        commands[comnum] = (char*)malloc(strlen(token));
        strcpy(commands[comnum++], token);
        token = strtok(NULL, "&");
    }

    for(int i = 0; i < comnum; i++)
    {
        if(strchr(commands[i], '<'))                 // I/O redirection
            inprdct = 1;
        if(strstr(commands[i], ">>"))
            outrdcta = 1;
        else if(strchr(commands[i], '>'))
            outrdcto = 1;
        if(inprdct || outrdcta || outrdcto)
            redirectFiles(commands[i]);

        if(check == 1 || i != comnum-1)
        {
            bgfg_proc(commands[i], 1);             // background
            t = 0;
        }
        else
        {
            t = time(NULL);
            bgfg_proc(commands[i], 0);             // foreground
            t = time(NULL) - t;
        }
        free(commands[i]);
    }
}

void findCommand(char command1[], char tempcom[])
{  
    char temp[maxsize]; 
    strcpy(temp, command1);
    token = strtok(command1, " ");
    int newline = '\n';
    if(strchr(token, newline))
        token[strlen(token)-1] = '\0'; 

    if(strcmp(token, "echo") == 0)
    {
        t = time(NULL);
        echo();
        t = time(NULL) - t;
    }
    else if(strcmp(token, "pwd") == 0)
    {
        t = time(NULL);
        pwd();
        t = time(NULL) - t;
    }
    else if(strcmp(token, "cd") == 0)
    {
        t = time(NULL);
        cd();
        t = time(NULL) - t;
    }
    else if(strcmp(token, "ls") == 0)
    {
        t = time(NULL);
        ls();
        t = time(NULL) - t;
    }
    else if(strcmp(token, "pinfo") == 0)
    {
        t = time(NULL);
        pinfo();
        t = time(NULL) - t;
    }
    else if(strcmp(token, "history") == 0)
    {
        t = time(NULL);
        print_history();
        t = time(NULL) - t;
    }
    else if(strcmp(token, "discover") == 0)
    {
        t = time(NULL);
        discover();
        t = time(NULL) - t;
    }
    else if(strcmp(token, "jobs") == 0)
    {
        t = time(NULL);
        jobs();
        t = time(NULL) - t;
    }
    else if(strcmp(token, "sig") == 0)
    {
        t = time(NULL);
        sig();
        t = time(NULL) - t;
    }
    else if(strcmp(token, "fg") == 0)
    {
        t = time(NULL);
        fg();
        t = time(NULL) - t;
    }
    else if(strcmp(token, "bg") == 0)
    {
        t = time(NULL);
        bg();
        t = time(NULL) - t;
    }
    else if(strcmp(token, "exit") == 0)
    {
        exit(1);
    }
    else
    {
        t = time(NULL);
        bgfg_proc(tempcom, 0);
        t = time(NULL) - t;
    }
}


int input()
{
    inprdct = outrdcta = outrdcto = 0;
    buf = NULL;
    // size_t buf_len = 256;
    buf = (char*)malloc(1000);
    buf[0] = '\0';
    char c;
    int index = 0;
    struct termios original, raw;

    setbuf(stdout, NULL);
    tcgetattr(STDIN_FILENO, &original); //== -1);
    // {
    //     perror("tcgetattr");
    //     tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
    //     return;
    // }
    raw = original;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); //== -1) 
    // {
    //     perror("tcgetattr");
    //     tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
    //     return;
    // }

    while(read(STDIN_FILENO, &c, 1) == 1)
    {
        if(iscntrl(c))
        {
            if(c == 10) 
            {
                printf("\n");
                break;
            }
            else if(c == 127)
            {
                if(index > 0)
                {
                    if (buf[index-1] == 9) 
                    {
                        for (int i = 0; i < 7; i++) 
                            printf("\b");
                    }
                    buf[--index] = '\0';
                    printf("\b \b");
                }
            }
            else if(c == 9)
                tab(&index);
            else if(c == 4)
                exit(0);
        }
        else
        {
            printf("%c", c);
            buf[index++] = c;
        }
    }
    buf[index] = '\0';
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
    
    // getline(&buf, &buf_len, stdin);
    if(buf == NULL || strcmp(buf, "\n") == 0)
        return 0;

    char temp[256];
    strcpy(temp, buf);
    add_history();

    int count = 0;
    char* token2;

    token2 = strtok(temp, ";");
    while(token2)
    {
        token2 = strtok(NULL, ";");
        count++;
    }

    command = (char**)malloc(count*sizeof(char*));
    int count2 = 0;
    command[count2] = strtok(buf, ";");
    count2++;
    while(count2 < count)
        command[count2++] = strtok(NULL, ";");
    
    for(int i = 0; i < count; i++)
    {
        char tempcom[maxsize];
        strcpy(tempcom, command[i]);

        if(strchr(command[i], '|'))
        {
            int ret1 = pipeCommand(command[i]);
            if(ret1 == 1)
                continue;
            else if(ret1  == 0)
                printf("error: invalid piping\n");
            return 0;
        }


        if(strchr(command[i], '&'))                 // & processes  
        {
            and_proc(command[i]);
            continue;
        }

        if(strchr(command[i], '<'))                 // I/O redirection
            inprdct = 1;
        if(strstr(command[i], ">>"))
            outrdcta = 1;
        else if(strchr(command[i], '>'))
            outrdcto = 1;
        if(inprdct || outrdcta || outrdcto)
        {
            int ret = redirectFiles(command[i]);
            if(ret < 0)
                return 0;

            if(inprdct)
                command[i] = strtok(command[i], "<");
            else if(outrdcta)
                command[i] = strtok(command[i], ">>");
            else
                command[i] = strtok(command[i], ">");
        }

        findCommand(command[i], tempcom);

        if(inprdct)
            dup2(stdintemp, 0);
        
        if(outrdcta || outrdcto)
            dup2(stdouttemp, 1);
    }
}
