#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if(pid == -1)
        return 1;
    if(pid == 0)
    {
        int file = open("res.txt", O_WRONLY | O_CREAT, 0777);
        dup2(file, 1);
        int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
        if(err == -1)
        {
            printf("Couldn't find program to execute\n");
            return 2;
        }
    }
    else
    {
        int wstatus;
        waitpid(pid, &wstatus, 0);
        if (WIFEXITED(wstatus)) //возвращает true, если процесс завершился нормально, и false, если нет
        {
            int statusCode = WEXITSTATUS(wstatus);
            if(statusCode == 0)
            {
                printf("Succes!\n");
                execlp("grep", "grep", "round-trip", "res.txt", NULL);
            }
            else
                printf("Failure with status code %d\n", statusCode);
        }
    }
    return 0;
}


/*
int main()
{
    int fd[2];
    pipe(fd);

    pid_t pid = fork();
    if(pid == -1)
        return 1;
    if(pid == 0)
    { 
        fd[1] = open("res.txt", O_WRONLY | O_CREAT, 0777);
        dup2(fd[1], 1);
        int err = execlp("ls", "ls", "-l", NULL);
        if(err == -1)
        {
            printf("Couldn't find program to execute\n");
            return 2;
        }
    }
    else
    {
        int wstatus;
        waitpid(pid, &wstatus, 0);
        if (WIFEXITED(wstatus)) //возвращает true, если процесс завершился нормально, и false, если нет
        {
            int statusCode = WEXITSTATUS(wstatus);
            if(statusCode == 0)
            {
                printf("Succes!\n");
                execlp("wc", "wc", "-l", "res.txt", NULL);
            }
            else
                printf("Failure with status code %d\n", statusCode);
        }
    }
    return 0;
}*/