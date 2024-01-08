#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t p1 = fork();
    if(p1 == -1)
        return 1;
    if(p1 == 0)
    {
        //child1
        sleep(4);
        printf("Child1 finished execution %d\n", getpid());
        return 0; //не понимаю, почему это не завершает программу тут же
    }
    int p2 = fork();
    if(p2 == -1)
        return 2;
    if(p2 == 0)
    {
        //child2
        sleep(1);
        printf("Child2 finished execution %d\n", getpid());
        return 0;
    }
    // parent

    /*
    если я хочу завершить процессы в зависимости от длительности sleep :

    wait(NULL);
    wait(NULL);

    еще один вариант для проверки :
    int p1_res = wait(NULL);
    printf("Waited for %d\n", p1_res);
    (и тд)
    */
   
   //если я хочу сначала завершить конкретный процесс :

   int p2_res = waitpid(p2, NULL, 0);
   printf("Waited for %d\n", p2_res);

   int p1_res = waitpid(p1, NULL, 0);
   printf("Waited for %d\n", p1_res);
   return 0;
}