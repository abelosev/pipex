#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv, char **envp) //всегда вызывать exec в child process, чтобы мы могли вернуться к parent process
{
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("Error");
        return 1;
    }
    if(pid == 0)
    {
        char *arr[] = {"ping", "-c", "3", "google.com", NULL};
        char *env[] = {"TEST=environment variable", NULL};
        execve("/sbin/ping", arr, env);
        return 0;
    }
    wait(NULL);
    printf("Ping finished executing\n"); 
    return 0;
}