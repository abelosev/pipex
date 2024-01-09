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

void child1(t_pipex *p, char **av, char **envp)
{
    char *result = cmd_check(av[2], envp);
    if (result == NULL) 
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    else
    {
        p->arg_w_path[0] = cmd_check(av[2], envp);
        p->args_list1 = ft_split(av[2], 1);
        error_handler(dup2(p->fd_p[1], 1));
        close(p->fd_p[0]);
        error_handler(dup2(p->infile_fd, 0));
        execve(p->arg_w_path[0], p->args_list1, envp);
    }
}

void child2(t_pipex *p, char **av, char **envp)
{
    char *result = cmd_check(av[3], envp);
    if (result == NULL) 
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    else
    {
        p->arg_w_path[1] = cmd_check(av[3], envp);
        p->args_list2 = ft_split(av[3], 1);
        error_handler(dup2(p->fd_p[0], 0));
        close(p->fd_p[1]);
        error_handler(dup2(p->outfile_fd, 1));
        close(p->infile_fd);
        execve(p->arg_w_path[1], p->args_list2, envp);
    }
}

int main(int ac, char **av, char **envp)
{
    t_pipex p;

    input_handler(ac, envp);
    p.infile_fd = open(av[1], O_RDONLY);
    error_handler(p.infile_fd);
    p.outfile_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
    error_handler(p.outfile_fd);
    error_handler(pipe(p.fd_p));

    printf("все ок с аргументами!");

    p.pid1 = fork();
    error_handler(p.pid1);
    printf("все ок с первой форк!");

    if(p.pid1 == 0)
    { 
        printf("я в процессе1!");
        child1(&p, av, envp);
    }
    p.pid2 = fork();
    error_handler(p.pid2);

    if(p.pid2 == 0)
    {
        printf("я в процессе2!");
        child2(&p, av, envp);
    }
    printf("я в родительском процессе!");
    closing_fd(p);
    waitpid(p.pid1, NULL, 0);
    waitpid(p.pid2, NULL, 0);
    //freing_parent(&p);
    close(p.infile_fd);
    close(p.outfile_fd);
    return 0;
}