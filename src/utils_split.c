/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev@student.42.fr                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:06:17 by abelosev          #+#    #+#             */
/*   Updated: 2024/01/08 15:35:04 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	ft_is_delimiter(char c, char *delimiters)
{
	int	i;

	i = 0;
	while (delimiters[i])
	{
		if (c == delimiters[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_words_len(char *str, char *delimiters)
{
	int	idx;
	int	length;

	idx = 0;
	length = 0;
	while (str[idx] != '\0')
	{
		if (!ft_is_delimiter(str[idx], delimiters))
		{
			length++;
			idx++;
		}
		else
			idx++;
	}
	return (length);
}

char	*ft_get_word(char *str, char *delimiters)
{
	int			idx;
	char		*word;

	idx = 0;
	while (str[idx] != '\0' && !ft_is_delimiter(str[idx], delimiters))
		idx++;
	word = (char *)malloc(sizeof(char) * (idx + 1));
	if (!word)
		return (NULL);
	idx = 0;
	while (str[idx] != '\0' && !ft_is_delimiter(str[idx], delimiters))
	{
		word[idx] = str[idx];
		idx++;
	}
	word[idx] = '\0';
	return (word);
}

char	**ft_split(char *str, char *delimiters)
{
	int		idx;
	char	**split;

	idx = 0;
	split = (char **)malloc(sizeof(char *) * ft_words_len(str, delimiters) + 1);
	if (!split)
		return (NULL);
	while (*str)
	{
		while (*str && ft_is_delimiter(*str, delimiters))
			str++;
		if (*str && !ft_is_delimiter(*str, delimiters))
		{
			split[idx] = ft_get_word(str, delimiters);
			idx++;
		}
		while (*str && !ft_is_delimiter(*str, delimiters))
			str++;
	}
	split[idx] = NULL;
	return (split);
}
