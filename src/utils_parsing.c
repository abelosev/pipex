#include "../header/pipex.h"

char **get_path(char **envp) //убрать самую первую полученную строку (PATH) или просто начинать со строки 1
{ 
    char **res = NULL;
    while(*envp)
    {
        if(ft_strncmp("PATH=", *envp, 5) == 0)
        {
            res = ft_split(*envp + 5, ":");
        }
        envp++;
    }
    return (res);
}

char *cmd_check(char **args_list, char **envp) //need check for ./pipex infile "/usr/bin/cat"
{
    char **path_list = get_path(envp);
    if(path_list == NULL)
        return NULL; 
    else
    {
        int i = 0;
        while(path_list[i])
        {
            char *arg_w_path = ft_strjoin(ft_strjoin(path_list[i], "/"), args_list[0]);

            if(access(arg_w_path, F_OK) == 0)
            {
                return(arg_w_path);
            }
            else
                i++;
        }
    }
    free_array(path_list);
    return NULL;
}