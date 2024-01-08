#include "../header/pipex.h"

int ft_strlen(char *s)
{
    int i = 0;
    while(s[i])
        i++;
    return i;
}

char *ft_strjoin(char *s1, char *s2)
{
    int len = ft_strlen(s1) + ft_strlen(s2) + 1;
    char *res = (char*)malloc(sizeof(char) * len);
    if(!res)
        return NULL;
    int i = 0;
    int k = 0;
    while(s1[i] && i < len - 1)
    {
        res[i] = s1[i];
        i++;
    }
    while(s2[k] && i < len - 1)
    {
        res[i] = s2[k];
        i++;
        k++;
    }
    res[i] = '\0';
    return (res);
}

int    ft_strncmp(char *s1, char *s2, int n)
{
    int i = 0;
    while(s1[i] && s2[i] && i < n)
    {
        if(s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return 0;
}