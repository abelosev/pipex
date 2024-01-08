#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    pid_t p = fork();
    if(p == -1)
        return 1;
    else if(p == 0)
    {
        sleep(1);
        printf("child process ID : %d, their parent ID : %d\n", getpid(), getppid());
    }
    else
    {
        printf("What fork returns : %d\n", p); //inside parent process : child process ID 
        printf("parent process ID : %d, their parent ID : %d\n", getpid(), getppid());
    }
    wait(NULL);
    return 0;
}