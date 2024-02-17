/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev@student.42.fr                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:06:17 by abelosev          #+#    #+#             */
/*   Updated: 2024/01/09 21:56:55 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	child1(t_pipex *p, char **av, char **envp)
{
	error_handler(dup2(p->fd_p[1], 1));
	close(p->fd_p[0]);
	close(p->outfile_fd);
	error_handler(dup2(p->infile_fd, 0));
	p->arg_w_path[0] = cmd_check(av[2], envp);
	p->args_list1 = ft_split(av[2], 1);
	if (p->arg_w_path == NULL || p->arg_w_path[0] == NULL
		|| p->args_list1 == NULL)
	{
		perror("Error");
		free_array(p->args_list1);
		free(p->arg_w_path[0]);
		exit(EXIT_FAILURE);
	}
	execve(p->arg_w_path[0], p->args_list1, envp);
	free(p->arg_w_path[0]);
	free_array(p->args_list1);
}

void	child2(t_pipex *p, char **av, char **envp)
{
	error_handler(dup2(p->fd_p[0], 0));
	close(p->fd_p[1]);
	close(p->infile_fd);
	error_handler(dup2(p->outfile_fd, 1));
	p->arg_w_path[1] = cmd_check(av[3], envp);
	if (p->arg_w_path == NULL || p->arg_w_path[1] == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	p->args_list2 = ft_split(av[3], 1);
	execve(p->arg_w_path[1], p->args_list2, envp);
	free(p->arg_w_path[1]);
	free_array(p->args_list2);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	p;

	input_handler(ac, envp);
	p.infile_fd = open(av[1], O_RDONLY);
	p.outfile_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	error_handler(p.outfile_fd);
	error_handler(pipe(p.fd_p));
	p.pid1 = fork();
	error_handler(p.pid1);
	if (p.pid1 == 0)
		child1(&p, av, envp);
	p.pid2 = fork();
	error_handler(p.pid2);
	if (p.pid2 == 0)
		child2(&p, av, envp);
	closing_fd(p);
	waitpid(p.pid1, NULL, 0);
	waitpid(p.pid2, NULL, 0);
	close(p.infile_fd);
	close(p.outfile_fd);
	return (0);
}
