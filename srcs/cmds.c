/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 21:21:41 by musoufi           #+#    #+#             */
/*   Updated: 2021/07/24 16:35:55 by musoufi          ###   ########lyon.fr   */
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

void	exec_cmd(t_token *token, char **env)
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
			execve(tmp, cmd, env);
		i++;
	}
}

void	exec_builtin()
{
	exit(0);
}

void	execution(t_token *token, char **env)
{
	if (is_builtin(token) == FALSE)
		exec_cmd(token, env);
	else
		exec_builtin();
}

void		status_child(pid_t pid)
{
	if (WIFEXITED(pid))
		wstatus = WEXITSTATUS(pid);
	if (WIFSIGNALED(pid))
	{
		wstatus = WTERMSIG(pid);
		if (wstatus != 131)
			wstatus += 128;
	}
}

static void	child(t_token *token, int fd[2], int *fdd)
{
	close(fd[0]);
	close(0);
	dup(*fdd);
	close(*fdd);
	if (token->next && strncmp(token->next->operator, "|", 2) == 0)
	{
		close(1);
		dup(fd[1]);
		close(fd[1]);
	}
}

int			run_pipe(t_token *token, char **env, int fdd)
{
	int		fd[2];
	pid_t 	pid;

	fd[0] = -1;
	fd[1] = -1;
	if (pipe(fd))
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		close(fdd);
		return (-1);
	}
	else if (!pid)
	{
		child(token, fd, &fdd);
		execution(token, env);
		exit(0);
		//ft_exit(cmdargs, 0);
	}
	wait(&pid);
	status_child(pid);
	close(fdd);
	close(fd[1]);
	return (fd[0]);
}

int fork_process(t_token *token, char **env)
{
	int fdd;
	
	fdd = dup(0);
	if (ft_strncmp(token->cmd, "exit", 4) == 0)
		return (write_exit());
	if (token->next == NULL)
		fdd = run_pipe(token, env, fdd);
	else
	{
		while ((token->next && strncmp(token->next->operator, "|", 2) == 0) || token->in)
		{
			fdd = run_pipe(token, env, fdd);
			if (token->out)
				token = token->next->next;
			else
				break;
		}
	}
	return (TRUE);
}

int		is_builtin(t_token *token)
{
	if (ft_strncmp(token->cmd, "echo", 4) == 0)
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
	return (FALSE);
}

/* ls | wc
http://www.zeitoun.net/articles/communication-par-tuyau/start
https://linux.die.net/man/2/waitpid
http://manpagesfr.free.fr/man/man2/fork.2.html
*/
