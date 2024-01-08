#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h> //для FIFO
#include <sys/types.h> //для FIFO
#include <time.h>
#include <errno.h>
#include <fcntl.h> //для open

int main()
{
    int arr[5];
    int fd = open("sum", O_RDONLY);
    if(fd == -1)
        return 1;
    int i;

    /* НЕОПТИМИЗИРОВАННЫЙ :
    for(i = 0; i < 5; i++)
    {
        if(read(fd, &arr[i], sizeof(int)) == -1)
            return 2;
        printf("Received %d\n", arr[i]);
    }
    */
   // ОПТИМИЗИРОВАННЫЙ : читаю array целиком
    if(read(fd, arr, sizeof(int) * 5) == -1)
        return 2;
    int sum_nb = 0;
    for(i = 0; i < 5; i++)
        sum_nb += arr[i];
    printf("The calculated sum_nb is %d\n", sum_nb);
    close(fd);
    fd = open("sum", O_WRONLY);
    if(write(fd, &sum_nb, sizeof(int)) == -1)
        return 3;
    close(fd);
    return 0;
}