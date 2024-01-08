#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h> //для FIFO
#include <sys/types.h> //для FIFO
#include <errno.h>
#include <fcntl.h> //для open

int main()
{
    if(mkfifo("myfifo1", 0777) == -1) //path, permission
    {
        if(errno != EEXIST)
        {
            printf("could not create a fifo file\n");
            return (1);
        } 
    } 
    printf("Opening...\n");
    //int fd = open("myfifo1", O_WRONLY); // only reading => зависнет без cat
    int fd = open("myfifo1", O_RDWR); // for reading and writing => все сработает
    if(fd == -1)
        return 3;
    printf("Got the fd\n");
    int x = 42;
    if(write(fd, &x, sizeof(x)) == -1)
        return 2;
    printf("Written\n");
    close(fd);
    printf("Closed\n");
    return (0);
}