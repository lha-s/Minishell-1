/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 20:36:39 by musoufi           #+#    #+#             */
/*   Updated: 2021/07/30 21:45:41 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**strenv(char *s, char **env)
{
	char **dst;
	dst = ft_split(my_getenv(s, env) + ft_strlen(s), ':');
	return (dst);
}

char *build_line(char **tab, char *line)
{
	int i;

	i = 0;
	while (tab[i])
	{
		line = ft_strjoin(line, tab[i]);
		line = ft_strjoin(line, " ");
		i++;
	}
	return (line);
}

char**	build_cmd(t_token *token)
{
	char **cmd;
	char *line;

	if (token->option == NULL && token->arg == NULL)
		return (ft_split(token->cmd, ' '));
	line = ft_strjoin(token->cmd, " ");
	if (token->option)
		line = build_line(token->option, line);
	if (token->arg)
		line = build_line(token->arg, line);
	cmd = ft_split(line, ' ');
	free(line);
	return (cmd);
}

int			ft_check_sep(char s, char c)
{
	if (c == s)
		return (1);
	else
		return (0);
}

unsigned int	number_of_words(char const *s, char c)
{
	int i;
	int words_nb;
	int in_word;

	in_word = 0;
	words_nb = 0;
	i = 0;
	while (s[i])
	{
		if (ft_check_sep(s[i], c) == 0)
		{
			if (in_word == 0)
			{
				words_nb++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (words_nb);
}

char	**bin(t_token *token, t_shell **shell, char ***cmd)
{
	int i;
	char **path;
	char **tab;

	i = 0;
	tab = malloc(sizeof(char *) * (number_of_words((*cmd)[0], ' ') + 2)); //protéger le malloc ?
	path = strenv("PATH", (*shell)->env);
	while (path[i])
	{
		tab[i] = ft_strjoin(path[i], "/");
		tab[i] = ft_strjoin(tab[i], ft_strnstr(token->cmd, (*cmd)[0], ft_strlen((*cmd)[0])));
		i++;
	}
	return (tab);
}

void	exec_cmd(t_token *token, t_shell **shell)
{
	int i;
	char **tab;
	char **cmd;
	struct stat buf;

	i = 0;
	cmd = build_cmd(token);
	tab = bin(token, shell, &cmd);
	while (tab[i])
	{
		if (stat(tab[i], &buf) == 0)
			execve(tab[i], cmd, (*shell)->env);
		i++;
	}
	write_errors(2, token->cmd);
	exit_prog(&token, FALSE);
}

void	exec_cmd_fork(t_token *token, t_shell **shell)
{
	int i;
	char **tab;
	char **cmd;
	struct stat buf;
	pid_t pid;

	i = 0;
	cmd = build_cmd(token);
	tab = bin(token, shell, &cmd);
	pid = fork();
	if (pid < 0)
		ft_putstr_fd("fail\n", 2);
	else if (!pid)
	{
		while (tab[i])
		{
			if (stat(tab[i], &buf) == 0)
				execve(tab[i], cmd, (*shell)->env);
			i++;
		}
		write_errors(2, token->cmd);
		exit_prog(&token, FALSE);	
	}
	wait(&pid);
}