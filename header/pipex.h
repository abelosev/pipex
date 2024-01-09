/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelosev@student.42.fr                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:06:17 by abelosev          #+#    #+#             */
/*   Updated: 2024/01/08 15:35:04 by abelosev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
    #define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

typedef struct s_pipex {
    int fd_p[2];
    int infile_fd;
    int outfile_fd;
    pid_t pid1;
    pid_t pid2;
    char *arg_w_path[2];
    char **args_list1;
    char **args_list2;

} t_pipex;

void input_handler(int ac, char **envp);
void	free_array(char **arr);
void	error_handler(int value);
void freing_parent(t_pipex *p);
void closing_fd(t_pipex p);
void child1(t_pipex *p, char **av, char **envp);
void child2(t_pipex *p, char **av, char **envp);

int	ft_is_delimiter(char c, int flag);
int	ft_words_len(char *str, int flag);
int ft_strlen(const char *s);
int    ft_strncmp(char *s1, char *s2, int n);

char	*ft_get_word(char *str, int flag);
char	**ft_split(char *str, int flag);
char *ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char **get_path(char **envp);
char *path_check(char **path_list, char **args_list);
char	*cmd_check(char *arg, char **envp);
char	**args_list_check(char *arg);

#endif