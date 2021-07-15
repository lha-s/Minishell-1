/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 21:21:41 by musoufi           #+#    #+#             */
/*   Updated: 2021/07/15 21:13:48 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**strenv(char *s)
{
	char **dst;
	dst = ft_split(getenv(s) + ft_strlen(s), ':');
	return (dst);
}

void	exec_cmd(t_token *token, char **env)
{
	int i;
	char **path;
	char *tmp;
	struct stat buf;
	char **cmd;

	cmd = ft_split(token->cmd, ' ');
	i = 0;
	path = strenv("PATH=");
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, ft_strnstr(token->cmd, cmd[0], ft_strlen(cmd[0])));
		if (stat(tmp, &buf) == 0)
			execve(tmp, cmd, env);
		i++;
	}
}

int exec_cmd_(t_token* s, char* env[])
{

	int old_in = s->fd[0];

	if (s->out && pipe(s->fd) < 0)
	{
		printf("pipe failed\n");
		return (write_errors(3, NULL));
	}

	pid_t pid = fork();
	if (pid == 0)
	{
			if (s->out)
			{
				dup2(s->fd[1], STDOUT_FILENO);
				close(s->fd[1]);
			}
			if (s->in)
			{
				dup2(old_in, STDIN_FILENO);
				close(old_in);
			}
			exec_cmd(s, env);
			// error
			exit(1);
	}
	else if (pid > 0)
	{
		s->pids[s->pid_index++] = pid;

		if (s->out)
			close(s->fd[1]);
		if (s->in)
			close(s->fd[0]);
	}
	else
		; // error
	return (TRUE);
}

int		cmd_selector(t_token *token, char **env)
{
	while (token != NULL)
	{
		if (ft_strcmp(token->cmd, "exit") == 0)
			return (write_exit());
		else if (ft_strcmp(token->cmd, "echo") == 0)
			return (echo_process(token));
		else if (ft_strcmp(token->cmd, "cd") == 0)
			return (TRUE);
		else if (ft_strcmp(token->cmd, "pwd") == 0)
			return (pwd_process());
		else if (ft_strcmp(token->cmd, "export") == 0)
			return (TRUE);
		else if (ft_strcmp(token->cmd, "unset") == 0)
			return (TRUE);
		else if (ft_strcmp(token->cmd, "env") == 0)
			return (TRUE);
		exec_cmd_(token, env);
		token = token->next;
	}
	return (TRUE);
}

/*
http://www.zeitoun.net/articles/communication-par-tuyau/start
https://linux.die.net/man/2/waitpid
http://manpagesfr.free.fr/man/man2/fork.2.html
*/
