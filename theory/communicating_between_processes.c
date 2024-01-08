#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

//задача: input a number in a child process, send it to the parent process and show on the screen

int main()
{
    int fd[2];
    if(pipe(fd) == -1)
        return (1);
    pid_t id = fork(); //fd скопируются в дочерний процесс, но будут существовать независимо друг от друга, так что их можно спокойно закрывать
    if(id == -1)
        return 4;
    if(id == 0)
    {
        close(fd[0]);
        printf("Put a number : ");
        int nb;
        scanf("%d", &nb);
        printf("You put %d\n", nb);
        if(write(fd[1], &nb, sizeof(int)) == -1)
            return 2;
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int y;
        if(read(fd[0], &y, sizeof(int)) == -1)
            return 3;
        close(fd[0]);
        y = y * 3;
        printf("Look what I've got from the child process : %d\n", y);
    }
    return (0);
}