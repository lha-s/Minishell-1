/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 00:58:10 by musoufi           #+#    #+#             */
/*   Updated: 2021/07/27 00:58:11 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**strenv(char *s)
{
	char **dst;
	dst = ft_split(getenv(s) + ft_strlen(s), ':');
	return (dst);
}

char**	build_cmd(t_token *token)
{
	char **cmd;
	char *tmp;
	int i;

	i = 0;
	if (token->option == NULL)
		return (ft_split(token->cmd, ' '));
	tmp = ft_strjoin(token->cmd, " ");
	while (token->option[i])
	{
		tmp = ft_strjoin(tmp, token->option[i]);
		tmp = ft_strjoin(tmp, " ");
		i++;
	}
	cmd = ft_split(tmp, ' ');
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
	path = strenv("PATH=");
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, ft_strnstr(token->cmd, cmd[0], ft_strlen(cmd[0])));
		if (stat(tmp, &buf) == 0)
			execve(tmp, cmd, (*shell)->env);
		i++;
	}
}