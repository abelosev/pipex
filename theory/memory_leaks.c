#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int a; //глобальная переменная - деаллоцируется с завершением exec программы
int main(int ac, char **av)
{
    int i; //статическая переменная, на stack - деаллоцируется с завершением работы функции
    int *b = malloc(sizeof(int)); //динамическая переменная, на heap - нужно free вручную
    *b = 5;
    printf("%d\n", *b);
    return 0;
}

