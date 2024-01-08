#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv, char **envp)
{
    //execlp("ping", "/sbin/ping", "google.com", NULL);

    /*char *arr[] = {
        "ping",
        "google.com",
        NULL
    };
    execvp("ping", arr);*/

    char *arr[] = {"ping", "google.com", NULL};
    char *env[] = {"TEST=environment variable", NULL};
    execve("/sbin/ping", arr, env);
    
    int err = errno;
    perror("Error");
    printf("Error : %s\n", strerror(err));
    printf("Ping finished executing\n"); //ne s'affiche pas, потому что весь исполняемый файл заменен ping
    return 0;
}