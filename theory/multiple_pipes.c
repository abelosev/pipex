#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/*какие будут pipes для структуры на рисунке?

1) writing from parent - reading to child1 : fd[0][1] - fd[0][0]
2) writing from child1 - reading to child2 : fd[1][1] - fd[1][0]
3) writing from child2 - reading to parent : fd[2][1] - fd[2][0]

Тогда дескрипторы, которые нужно оставить открытыми для child1: fd[0][0] и fd[1][1]
и тд
*/

int main()
{
    int fd[3][2];
    int i;
    for(i = 0; i < 3; i++)
    {
        if(pipe(fd[i]) < 0)
            return 1;
    }
    int x = 0;
    pid_t p1 = fork();
    if(p1 < 0)
        return 2;
    else if(p1 == 0)
    {
        //child1 process, their descriptors: fd[0][0], fd[1][1]
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);
        if(read(fd[0][0], &x, sizeof(int)) == -1)
            return 3;
        printf("Read to child1 : %d\n", x);
        x *= 4;
        if(write(fd[1][1], &x, sizeof(int)) == -1)
            return 4;
        printf("Written from child1 : %d\n", x);
        close(fd[0][0]);
        close(fd[1][1]);
    }
    else
    {
        pid_t p2 = fork();
        if(p2 == -1)
            return 5;
        else if(p2 == 0)
        {
            //child2 process, their descriptors : fd[1][0], fd[2][1]
            close(fd[0][0]);
            close(fd[0][1]);
            close(fd[1][1]);
            close(fd[2][0]);
    
            if(read(fd[1][0], &x, sizeof(int)) == -1)
                return 6;
            printf("Read to child2 : %d\n", x);
            x *= 4;
            if(write(fd[2][1], &x, sizeof(int)) == -1)
                return 7;
            printf("Written from child2 : %d\n", x);
            close(fd[1][0]);
            close(fd[2][1]);
        }
        else
        {
            //parent process, their descriptors: fd[0][1], fd[2][0]
            close(fd[0][0]);
            close(fd[1][0]);
            close(fd[1][1]);
            close(fd[2][1]);
            x = 5;
            if(write(fd[0][1], &x, sizeof(int)) == -1)
                return 8;
            printf("Written from parent : %d\n", x);
            if(read(fd[2][0], &x, sizeof(int)) == -1)
               return 9;
            printf("Read to parent, final result : %d\n", x);
            close(fd[0][1]);
            close(fd[2][0]);
            waitpid(p1, NULL, 0); //ето важно
            waitpid(p2, NULL, 0);
        }
    }
    return 0;
}