#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if(pid == 0) //в таком случае parent закончился раньше, чем child executed, так что 
                //у child появится новый parent
        sleep(5); //в таком случае могут быть проблемы с memory => обязательно добавлять следующий блок
    printf("Current process id : %d, their parent's id : %d\n", getpid(), getppid());
    int res = wait(NULL);
    if(res == -1)
        printf("No process to wait for\n");
    else
        printf("The process %d finished execution\n", res);
    return 0;
}