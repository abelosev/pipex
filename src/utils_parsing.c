/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev@student.42.fr                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:06:17 by abelosev          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/08 15:35:04 by abelosev         ###   ########.fr       */
=======
/*   Updated: 2024/01/08 15:50:53 by abelosev         ###   ########.fr       */
>>>>>>> 031f31dd141f9089f3d978758e5a34a23bb06f71
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

<<<<<<< HEAD
char **get_path(char **envp)
{ 
    char **res;
	res = NULL;
	if(envp == NULL || *envp == NULL)
	{
		perror("Envp");
		return NULL;
	}
    while (*envp)
    {
        if(ft_strncmp("PATH=", *envp, 5) == 0)
        {
            res = ft_split(*envp + 5, 2);
            if(res != NULL)
                return res;
        }
        envp++;
    }
	return NULL;
}

char *path_check(char **path_list, char **args_list)
{
	char *arg_w_path;
	int i;

	arg_w_path = NULL;
	i = 0;
	while (path_list[i])
	{
		arg_w_path = ft_strjoin(ft_strjoin(path_list[i], "/"), args_list[0]);
		if (access(arg_w_path, F_OK) == 0)
		{
			free_array(path_list);
			free_array(args_list);
			return (arg_w_path);
		}
		else
		{
			free(arg_w_path);
			i++;
		}
	}
	return(arg_w_path);
}

char	**args_list_check(char *arg, char **envp)
{
	char	**path_list;
	char	**args_list;

	if(ft_strlen(arg) == 0)
		return NULL;
	path_list = get_path(envp);
	if (path_list == NULL)
		return (NULL);
	args_list = ft_split(arg, 1);
	if(args_list == NULL || ft_strlen(args_list[0]) == 0)
	{
		free_array(path_list);
		return NULL;
	}
	free (path_list);
	return (args_list);
}

char	*cmd_check(char *arg, char **envp)
{
	char	**path_list;
	char	*arg_w_path;
	char	**args_list;

	arg_w_path = NULL;
	path_list = get_path(envp);
	if (path_list == NULL)
		return (NULL);
	args_list = args_list_check(arg, envp);
	if(args_list[0][0] == '/' && (access(args_list[0], F_OK) == 0))
		arg_w_path = ft_strdup(args_list[0]);
	else
		arg_w_path = path_check(path_list, args_list);
	free_array(path_list);
	free_array(args_list);
	return (arg_w_path);
}
=======
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
>>>>>>> 031f31dd141f9089f3d978758e5a34a23bb06f71
