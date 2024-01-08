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

void error_handler(int value);
void free_array(char **arr);
int *check_files(char *s1, char *s2);
int ft_strlen(char *s);
char *ft_strjoin(char *s1, char *s2);
int    ft_strncmp(char *s1, char *s2, int n);
char **get_path(char **envp);
char *cmd_check(char **args_list, char **envp);
int	ft_is_delimiter(char c, char *delimiters);
int	ft_words_len(char *str, char *delimiters);
char	*ft_get_word(char *str, char *delimiters);
char	**ft_split(char *str, char *delimiters);

#endif