#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    char text[100];
    printf("Type something : ");
    scanf("%s", text);
    printf("You typed : %s\n", text);
    return 0;
}