/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 21:21:41 by musoufi           #+#    #+#             */
/*   Updated: 2021/07/13 23:41:51 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**strenv(char *s)
{
	char **dst;
	dst = ft_split(getenv(s) + ft_strlen(s), ':');
	return (dst);
}

/*colle la commande à ses options*/
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

/*executer la commande dans le bon path*/
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

/*ouvre et ferme les pipe en fonction du type processus (parent ou enfant)*/
void	 cfg_piping(t_token *token, pid_t pid, int old_in)
{
	if (token->out)
	{
		if (pid == 0)
			dup2(token->fd[1], STDOUT_FILENO);
		close(token->fd[1]);
	}
	if (token->in)
	{
		if (pid == 0)
		{
			dup2(old_in, STDIN_FILENO);
			close(old_in);
		}
		else
			close(token->fd[0]);
	}
}

void	recursive_process(t_token *token, char **env)
{
	if (token->next && strncmp(token->next->operator, "|", 2) == 0)
	{
		fork_process(token->next->next, env);
	}
	if (is_builtin(token) == FALSE)
		exec_cmd(token, env);
	else
		exec_builtin();
}

int fork_process(t_token *token, char **env)
{
	int old_in;
	
	old_in = token->fd[0];
	if (ft_strncmp(token->cmd, "exit", 4) == 0)
		return (write_exit());
	if (token->out && pipe(token->fd) < 0)
	{
		printf("Error: pipe failed\n");
		return (FALSE);
	}
	pid_t pid = fork();
	if (pid == 0)
	{
		write(1, "TEST\n", 5);
		cfg_piping(token, pid, old_in);
		recursive_process(token, env);
		write_output("Error: fork had to be forced to quit\n");
		exit(0);
	}
	else if (pid > 0)
	{
		token->pids[token->pid_index++] = pid;
		cfg_piping(token, pid, old_in);
		wait(&pid);
	}
	else
		write_output("Error: fork failed, command failed\n");
	return (TRUE);
}

/*indique si la commande est un builtin (TRUE) ou pas (FALSE)*/
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
