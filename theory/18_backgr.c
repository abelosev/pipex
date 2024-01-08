#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

//backgrounded process = stopped process
//Control-Z : to stop a process on terminal, fg : to launch it again 

int main()
{
    int x;
    printf("Input number : ");
    scanf("%d", &x);
    sleep(5);
    printf("Result %d * 5 = %d\n", x, x * 5);
    return 0;
}