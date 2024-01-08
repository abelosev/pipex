#include "../header/pipex.h"

void error_handler(int value)
{
    if(value < 0)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
}

void free_array(char **arr)
{
    int len = 0;
    while(arr[len])
    {
        free(arr[len]);
        len++;
    }
    free(arr);
}

