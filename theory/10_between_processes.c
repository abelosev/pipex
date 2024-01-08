#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h> //для FIFO
#include <sys/types.h> //для FIFO
#include <time.h>
#include <fcntl.h> //для open
#include <sys/wait.h>

int main()
{
    int fd[2][2]; 
    // будут такие каналы : 
    //1) для передачи от родителя к ребенку fd[0][1]-fd[0][0]
    //2) для передачи от ребенка к родителю fd[1][1] - fd[1][0]

    int i;
    for(i = 0; i < 2; i++)
    {
        if(pipe(fd[i]) < 0)
            return 1;
    }
    pid_t p = fork();
    if(p == -1)
        return 2;
    if(p == 0)
    {
        close(fd[0][1]);
        close(fd[1][0]);
        printf("I'm in a child process\n");
        //child process
        int x;
        if(read(fd[0][0], &x, sizeof(int)) == -1)
            return 3;
        printf("X = %d is read to child\n", x);
        x *= 4;
        if(write(fd[1][1], &x, sizeof(int)) == -1)
            return 4;
        printf("X = %d is written from child\n", x);
        close(fd[1][1]);
        close(fd[0][0]);
        return 0;
    }
    close(fd[1][1]);
    close(fd[0][0]);
    int x = 5;
    printf("X is initialized\n");
    if(write(fd[0][1], &x, sizeof(int)) == -1)
        return 5;
    printf("X = %d is written from parent\n", x);
    if(read(fd[1][0], &x, sizeof(int)) == -1)
        return 6;
    printf("X = %d is read to parent\n", x);
    close(fd[0][1]);
    close(fd[1][0]);
    wait(NULL);
    return 0;
}