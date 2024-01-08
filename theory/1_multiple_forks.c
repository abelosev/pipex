#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h> //для open
#include <sys/wait.h>

#define PROCESS_NUM 3

int main()
{
    int i;
    pid_t pids[PROCESS_NUM];
    int p[PROCESS_NUM + 1][2];
    for(i = 0; i < PROCESS_NUM + 1; i++)
    {
        if(pipe(p[i]) == -1)
            return 1;
        i++;
    }
    for(i = 0; i < PROCESS_NUM; i++)
    {
        pids[i] = pifork();
        if(pids[i] < 0)
            return 2;
        if(pids[i] == 0)
        {
            //child process
            return 0;
        }

        for(i = 0; i < PROCESS_NUM; i++)
        {
            wait(NULL);
        }
    return 0;
}