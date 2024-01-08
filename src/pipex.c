/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev@student.42.fr                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:06:17 by abelosev          #+#    #+#             */
/*   Updated: 2024/01/08 12:08:24 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/pipex.h"

void input_handler(int ac, char **envp)
{
    if(envp == NULL || !envp)
    {
        perror("Envp doesn't exist");
        exit(EXIT_FAILURE);
    }

    if(ac != 5)
    {
        perror("Incorrect number of arguments");
        exit(EXIT_FAILURE);
    }
}

int main(int ac, char **av, char **envp)
{
    input_handler(ac, envp);

    int infile_fd = open(av[1], O_RDONLY);
    error_handler(infile_fd);

    int outfile_fd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
    error_handler(outfile_fd);

    int fd_p[2];
    error_handler(pipe(fd_p));

    char delimiters[] = {' ', '\t'};
    char **args_list1 = ft_split(av[2], delimiters);
    char **args_list2 = ft_split(av[3], delimiters);
    char *arg_w_path1 = cmd_check(args_list1, envp);
    char *arg_w_path2 = cmd_check(args_list2, envp);
    
    if(!arg_w_path1 || arg_w_path1 == NULL)
            exit(EXIT_FAILURE);
    if(!arg_w_path2 || arg_w_path2 == NULL)
            exit(EXIT_FAILURE);

    int pid1 = fork();
    error_handler(pid1);
    if(pid1 == 0)
    { 
        error_handler(dup2(fd_p[1], 1));
        close(fd_p[0]);
        error_handler(dup2(infile_fd, 0));
        execve(arg_w_path1, args_list1, envp);
    }
    else
    {
        int pid2 = fork();
        error_handler(pid2);

        if(pid2 == 0)
        {
            error_handler(dup2(fd_p[0], 0));
            close(fd_p[1]);
            error_handler(dup2(outfile_fd, 1));
            close(infile_fd);
            execve(arg_w_path2, args_list2, envp);
        }
        close(fd_p[0]);
        close(fd_p[1]);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
        free_array(args_list1);
        free_array(args_list2);
        free(arg_w_path1);
        free(arg_w_path2);
        close(infile_fd);
        close(outfile_fd);
    }
    return 0;
}