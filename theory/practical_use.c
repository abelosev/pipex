#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    int array[] = {1, 2, 3, 4, 5, 2};
    int fd[2];
    int start, end;
    int arrSize = sizeof(array) / sizeof(int);
    if(pipe(fd) == -1)
        return 1;
    pid_t id = fork();
    if(id == -1)
        return 2;
    else if(id == 0)
    {
        start = 0;
        end = arrSize / 2; // floored value, то есть для 7 элементов даст 3
    }
    else
    {
        start = arrSize / 2;
        end = arrSize;
    }

    int sum = 0;
    for(int i = start; i < end; i++)
    {
        sum = sum + array[i];
    }
    printf("Partial sum : %d\n", sum);

    if(id == 0)
    {
        close(fd[0]);
        if(write(fd[1], &sum, sizeof(int)) == -1)
            return 3;
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        int sum_child = 0;
        if(read(fd[0], &sum_child, sizeof(int)) == -1)
            return 4;
        sum += sum_child;
        close(fd[0]);
        printf("Whole sum : %d\n", sum);
        wait(NULL);
    }
    return 0;
}