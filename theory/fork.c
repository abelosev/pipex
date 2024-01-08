#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
    pid_t pid = fork();
    int n;
    if(pid > 0)
    {
        wait(NULL);
    }
    if(pid == 0)
    {
        n = 0;
        while(n <= 5)
        {
            printf("%d ", n);
            n++;
        }
    }
    else
    {
        int status;
        wait(&status);
        n = 6;
        while(n <= 10)
        {
            printf("%d ", n);
            n++;
        }
    }
    return (0);
}

//тренировка fork

/*int main()
{
    pid_t pid = fork();
    if(pid == 0)
    {
        printf("Это дочерний процесс, pid = %d\n", getpid());
    }
    else if(pid > 0)
    {
        printf("Это родительский процесс, pid = %d\n", getpid());
    }
    else
    {
        perror("ошибка");
        return 1;
    }
    return (0);
}*/