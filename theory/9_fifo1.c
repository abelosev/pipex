#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h> //для FIFO
#include <sys/types.h> //для FIFO
#include <errno.h>
#include <time.h>
#include <fcntl.h> //для open

int main()
{
    // creating fifo from the terminal using "mkfifo sum"
    int arr[5];
    srand(time(NULL));
    int i;
    for(i = 0; i < 5; i++)
    {
        arr[i] = rand() % 100;
        printf("Generated %d\n", arr[i]);
    }
    int fd = open("sum", O_WRONLY);
    if(fd == -1)
        return 1;

    /* НЕОПТИМИЗИРОВАННЫЙ ARR : через цикл FOR
    for(i = 0; i < 5; i++)
    {
        if(write(fd, &arr[i], sizeof(int)) == -1)
            return 2;
        printf("Wrote %d\n", arr[i]);
    }*/

    // ОПТИМИЗИРОВАННЫЙ ARR: 

    if(write(fd, arr, sizeof(int) * 5) == -1) // arr - это первый элемент массива
        return 2;
    close(fd);
    fd = open("sum", O_RDONLY);
    int sum_nb;
    if(read(fd, &sum_nb, sizeof(int)) == -1)
        return 2;
    printf("The received sum_nb is %d\n", sum_nb);
    close(fd);
    return 0;
}