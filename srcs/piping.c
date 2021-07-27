/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.C                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 20:36:47 by musoufi           #+#    #+#             */
/*   Updated: 2021/07/27 20:49:03 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_status(t_token **token, pid_t pid)
{
	int i;
	int wstatus;

	i = 0;
	while (*token && i < (*token)->pid_index)
	{
		waitpid((*token)->pids[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			wret = WEXITSTATUS(wstatus);
		if (WIFSIGNALED(pid))
		{
			wret = WTERMSIG(pid);
			if (wret != 131)
				wret += 128;
		}
		(*token)->pids[i] = 0;
		i++;
	}
}

void		pip(int *a, int *b, int *c, int close_all)
{
	if (close_all == TRUE)
	{
		close(*a);
		close(*b);
		close(*c);
	}
	else
	{
		close(*a);
		dup(*b);
		close(*c);
	}
}

void	child(t_token *token, t_shell **shell, int fd[2], int *fdd)
{
	int out;
	int in;

	out = 1;
	in = 0;
	close(fd[0]);
	pip(&in, fdd, fdd, FALSE);
	if (token->next && strncmp(token->next->operator, "|", 2) == 0)
		pip(&out, &fd[1], &fd[1], FALSE);
	execution(token, shell);
	exit_prog(&token, FALSE);
}

int			fork_process(t_token *token, t_shell **shell, int fdd)
{
	int 	fd[2];
	pid_t 	pid;
	
	fd[0] = -1;
	fd[1] = -1;
	if (pipe(fd))
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		pip(&fd[0], &fd[1], &fdd, TRUE);
		return (-1);
	}
	else if (!pid)
		child(token, shell, fd, &fdd);
	//exit_status(&token);
	wait(&pid);
	pip(&fdd, &fdd, &fd[1], TRUE);
	return (fd[0]);
}
