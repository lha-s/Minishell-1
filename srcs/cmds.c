/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 21:21:41 by musoufi           #+#    #+#             */
/*   Updated: 2021/07/24 16:29:34 by musoufi          ###   ########lyon.fr   */
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
		{
			dup2(token->fd[1], STDOUT_FILENO);
		}
		close(token->fd[1]);
	}
	if (token->in)
	{
		if (pid == 0)
		{
			dup2(old_in, STDIN_FILENO);
			close(old_in);
		}
		close(token->fd[0]);
	}
}

void	execution(t_token *token, char **env)
{
	g_pid = 0;
	if (is_builtin(token) == FALSE)
		exec_cmd(token, env);
	else
		exec_builtin();
}

void		status_child(void)
{
	if (WIFEXITED(g_pid))
		g_status = WEXITSTATUS(g_pid);
	if (WIFSIGNALED(g_pid))
	{
		g_status = WTERMSIG(g_pid);
		if (g_status != 131)
			g_status += 128;
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
	status_child();
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

int fork_process_(t_token *token, char **env, int old_in)
{
	//int old_in;
	int wstatus;
	int wret;

	wret = 0;
	if (ft_strncmp(token->cmd, "exit", 4) == 0)
		return (write_exit());
	if (pipe(token->fd) < 0)
	{
		printf("Error: pipe failed\n");
		return (FALSE);
	}
	if (old_in < 0)
		old_in = token->fd[0];
	fprintf(stderr, "old_in = %d\n", old_in);
	pid_t pid = fork();
	if (pid == 0)
	{
		char buf;
		if (strncmp(token->cmd, "wc", 3) == 0)
			//fscanf(stdin, "%s\n", &buf);
		fprintf(stderr, "WC=%s\n", &buf);
		fprintf(stderr, "%s fd0= %d, fd1= %d\n", token->cmd, token->fd[0], token->fd[1]);

		if (token->out)
		{
			close(token->fd[0]);
			dup2(token->fd[1], STDOUT_FILENO);
			close(token->fd[1]);
		}
		if (token->in)
		{
			close(token->fd[1]);
			dup2(token->fd[0], STDIN_FILENO);
			close(token->fd[0]);
		}

		if (is_builtin(token) == FALSE)
			exec_cmd(token, env);
		else
			exec_builtin();

		//cfg_piping(token, pid, old_in);
		write_output("Error: fork had to be forced to quit\n");
		exit(0);
	}
	else if (pid > 0)
	{
		token->pids[token->pid_index++] = pid;

		/*if (token->out)
		{
			close(token->fd[0]);
			dup2(token->fd[1], STDOUT_FILENO);
		}*/
		if (token->in)
		{
			close(token->fd[0]); //fd[Ø] de pipe ls
			dup2(token->fd[old_in], STDIN_FILENO);
			close(token->fd[old_in]);
		}

		//cfg_piping(token, pid, old_in);
		waitpid(pid, &wstatus, 0);
		char buffer[BUFSIZ];
		read(token->fd[0], buffer, BUFSIZ);
		fprintf(stderr, "pipe=%s\n", buffer);
		recursive_process(token, env, old_in);
		if (WIFEXITED(wstatus))
			wret = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			wret =  128 + WTERMSIG(wstatus);
		//printf("EXIT STATUS=%d\n", wret);
	}
	else
		write_output("Error: fork failed, command failed\n");
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
