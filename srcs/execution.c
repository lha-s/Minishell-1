/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 20:36:39 by musoufi           #+#    #+#             */
/*   Updated: 2021/07/30 19:18:34 by allanganoun      ###   ########.fr       */
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

void	exec_cmd(t_token *token, t_shell **shell)
{
	int i;
	char **path;
	char *tmp;
	struct stat buf;
	char **cmd;

	cmd = build_cmd(token);
	i = 0;
	path = strenv("PATH", (*shell)->env);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp,
			ft_strnstr(token->cmd, cmd[0], ft_strlen(cmd[0])));
		if (stat(tmp, &buf) == 0)
			execve(tmp, cmd, (*shell)->env);
		i++;
	}
	write_errors(2, token->cmd);
}
