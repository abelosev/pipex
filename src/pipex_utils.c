/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev@student.42.fr                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:06:17 by abelosev          #+#    #+#             */
/*   Updated: 2024/01/08 15:37:56 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

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
