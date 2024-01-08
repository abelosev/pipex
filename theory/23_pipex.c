#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp) //всегда вызывать exec в child process, чтобы мы могли вернуться к parent process
{
    int fd[3][2];
    int i;

    for(i = 0; i < 3; i++)
    {
        if(pipe(&fd[i][0]) == -1 || pipe(&fd[i][1]) == -1)
        {
            perror("Error");
            return 1;
        }
    }
    pid_t pid1 = fork();
    if(pid1 == -1)
    {
        perror("Error");
        return 2;
    }
    if(pid1 == 0)
    {
        //child 1 : fd[0][0], fd[1][1]
        close(fd[1][0]);
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[2][0]);
        close(fd[2][1]);

        fd[1][1] = open("child1.txt", O_WRONLY | O_CREAT, 0777);
        dup2(fd[1][1], 1);
        char *arr[] = {"ls", "-l", NULL};
        char *env[] = {"TEST=environment variable", NULL};
        execve("/bin/ls", arr, env);
        dup2(fd[1][0], fd[1][1]);
        close(fd[1][1]);
        return 0;
    }

    waitpid(pid1, NULL, 0);
    pid_t pid2 = fork();
    if(pid2 == -1)
    {
        perror("Error");
        return 4;
    }

    if(pid2 == 0)
    {
        //child2 : fd[1][0], fd[2][1]
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);

       //open(&fd[1][0], O_RDONLY);
        fd[2][1] = open("parent.txt", O_WRONLY | O_CREAT, 0777);
        dup2(fd[2][1], 1);
        char *arr[] = {"wc", "-l", NULL};
        char *env[] = {"TEST=environment variable", NULL};
        execve("/bin/wc", arr, env);
        close(fd[2][1]);
        close(fd[1][0]);
        return 0;
    }

    //parent : fd[0][1], fd[2][0]
    
    waitpid(pid2, NULL, 0);

    close(fd[0][0]);
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[2][1]);
    fd[2][0] = open("res.txt", O_RDONLY | O_CREAT, 0777);
    return 0;
}