#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
    int pid = fork();
    if(pid == -1)
        return 1;
    if(pid == 0)
    {
        //child
        while(1)
        {
            printf("It is an infinite loop\n");
            usleep(60000);
        }
    }
    else
    {
        sleep(1);
        kill(pid, SIGSTOP); //to pause
        sleep(3);
        kill(pid, SIGCONT); //to continue
        sleep(1);
        kill(pid, SIGKILL); //to terminate child process
        wait(NULL);
    }
    return 0;
}