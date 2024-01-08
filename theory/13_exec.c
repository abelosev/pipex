#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp)
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
        int err = execve("/sbin/ping", arr, env);
        if(err == -1)
        {
            perror("Error");
            return 2;
        }
    }
    else
    {
        int wstatus;
        waitpid(pid, &wstatus, 0);
        if (WIFEXITED(wstatus)) //возвращает true, если процесс завершился нормально, и false, если нет
        {
            int statusCode = WEXITSTATUS(wstatus);
            if(statusCode == 0)
                printf("Succes!\n");
            else
            {
                printf("Failure with status code %d\n", statusCode);
            }
        }
        printf("Ping finished executing\n"); 
    }
    return 0;
}