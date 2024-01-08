/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev@student.42.fr                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:06:17 by abelosev          #+#    #+#             */
/*   Updated: 2024/01/08 15:50:53 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

char	**get_path(char **envp)
{
	char	**res;

	res = NULL;
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			res = ft_split(*envp + 5, ":");
		envp++;
	}
	return (res);
}

char	*cmd_check(char **args_list, char **envp)
{
	char	**path_list;
	char	*arg_w_path;
	int		i;

	path_list = get_path(envp);
	if (path_list == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (path_list[i])
		{
			arg_w_path = ft_strjoin(ft_strjoin(path_list[i], "/"),
					args_list[0]);
			if (access(arg_w_path, F_OK) == 0)
				return (arg_w_path);
			else
				i++;
		}
	}
	free_array(path_list);
	return (NULL);
}
