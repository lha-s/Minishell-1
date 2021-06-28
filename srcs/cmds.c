/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 21:21:41 by musoufi           #+#    #+#             */
/*   Updated: 2021/06/28 20:14:29 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**strenv(char **env, char *s)
{
	char **dst;
	int ret;
	int i;

	i = 0;
	ret = 1;
	while (ret != 0)
	{
		ret = ft_strncmp(env[i], s, ft_strlen(s));
		i++;
	}
	dst = ft_split(env[i - 1] + ft_strlen(s), ':');
	return (dst);
}

void	exec_cmd(char *line, char **env)
{
	int i;
	char **path;
	char *tmp;
	struct stat buf;
	char **cmd;

	cmd = ft_split(line, ' ');
	i = 0;
	path = strenv(env, "PATH=");
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, ft_strnstr(line, cmd[0], ft_strlen(cmd[0])));
		if (stat(tmp, &buf) == 0)
			execve(tmp, cmd, env);
		i++;
	}
}

void	exec_child(char *line, char **env, int pfd[2])
{
	close(pfd[1]);
	exec_cmd(line, env);
}

void	exec_parent(int pfd[2])
{
	close(pfd[0]);
	//Continuer quand tu aura une liste chainée pour passer sur la cmd suivante
	//chercher si y a encore un pipe "|"" pour execve recusive
	//regarder prochain element de la liste chainée
}

int 	exec_else(char *line, char **env)
{
	int pfd[2];

	if (pipe(pfd) == 0)
		exec_child(line, env, pfd);
	else if (pipe(pfd) != -1)
	{
		//wait l'execution du child
		exec_parent(pfd);
		//do shit
	}
	return (TRUE);
}

int		cmd_selector(t_token *token, char **env)
{
	if (ft_strncmp(token->cmd, "exit", 4) == 0)
		return (write_exit());
	else if (ft_strncmp(token->cmd, "echo", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(token->cmd, "cd", 2) == 0)
		return (TRUE);
	else if (ft_strncmp(token->cmd, "pwd", 3) == 0)
		return (TRUE);
	else if (ft_strncmp(token->cmd, "export", 6) == 0)
		return (TRUE);
	else if (ft_strncmp(token->cmd, "unset", 5) == 0)
		return (TRUE);
	else if (ft_strncmp(token->cmd, "env", 3) == 0)
		return (TRUE);
	return (exec_else(token->cmd, env));
}

/*
Pipe
Fork -> recup pid du fils
si 0 : fil, si != -1 : père
kill fils quand terminé

http://www.zeitoun.net/articles/communication-par-tuyau/start
https://linux.die.net/man/2/waitpid
http://manpagesfr.free.fr/man/man2/fork.2.html
*/
