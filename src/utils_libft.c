/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev@student.42.fr                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:06:17 by abelosev          #+#    #+#             */
/*   Updated: 2024/01/08 15:30:28 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		len;
	int		i;
	int		k;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = (char *)malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] && i < len - 1)
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[k] && i < len - 1)
	{
		res[i] = s2[k];
		i++;
		k++;
	}
	res[i] = '\0';
	return (res);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
