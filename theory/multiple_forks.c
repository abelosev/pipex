#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

// важное замечание: если пытаешься создать кучу процессов, создавай их все из главного родительского процесса!

int main()
{
    pid_t pid1 = fork();
    pid_t pid2 = fork();
    if(pid2 == 0)
    {
        if(pid1 == 0)
            printf("Я внук главного процесса\n");
        else
            printf("Я ребенок главного процесса в параллельной ветви\n");
    }
    else
    {
        if(pid1 == 0)
        {
            sleep(1);
            printf("%d\n", getppid());
            printf("Я самый первый ребенок главного процесса в основной ветви\n");
        }
        else
        {
            printf("Я главный процесс\n");
            printf("%d\n", getpid());
        }
    }
    //wait(NULL); так оставлять нельзя, иначе родительский процесс завершится раньше, чем самый первый ребенок закончит выполнение
    while(wait(NULL) != -1 || errno != ECHILD)
        printf("Waiting for a child to finish\n");

    /*
    while (wait(NULL) != -1 || errno != ECHILD)
    ; //можно просто оставить пустой оператор в теле цикла
    */
    return 0;
}