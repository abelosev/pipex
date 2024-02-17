/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev@student.42.fr                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:06:17 by abelosev          #+#    #+#             */
/*   Updated: 2024/01/09 20:47:05 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	input_handler(int ac, char **envp)
{
	if (envp == NULL)
	{
		perror("Envp doesn't exist");
		exit(EXIT_FAILURE);
	}
	if (ac != 5)
	{
		perror("Incorrect number of arguments");
		exit(EXIT_FAILURE);
	}
}

void	error_handler(int value)
{
	if (value < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

void	free_array(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
	{
		free(arr[len]);
		len++;
	}
	free(arr);
}

void	closing_fd(t_pipex p)
{
	close(p.fd_p[0]);
	close(p.fd_p[1]);
}
