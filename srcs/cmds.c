/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 21:21:41 by musoufi           #+#    #+#             */
/*   Updated: 2021/07/29 17:16:24 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int run_process(t_token *token, t_shell **shell)
{
	int fdd;

	fdd = dup(0);
	if (ft_strcmp(token->cmd, "exit") == 0)
		exit_prog(&token, TRUE);
	if (token->next == NULL)
		fdd = fork_process(token, shell, fdd);
	else
	{
		while ((token->next && strncmp(token->next->operator, "|", 2) == 0) || token->in)
		{
			fdd = fork_process(token, shell, fdd);
			if (token->out)
				token = token->next->next;
			else
				break; //changer ça
		}
	}
	close(fdd);
	return (TRUE);
}

void		exec_builtin(t_token *token, t_shell **shell)
{
	if (ft_strcmp(token->cmd, "exit") == 0)
		exit_prog(&token, FALSE);
	else if (ft_strcmp(token->cmd, "echo") == 0)
		echo_process(token, (*shell)->env);
	else if (ft_strcmp(token->cmd, "cd") == 0)
		return;
	else if (ft_strcmp(token->cmd, "pwd") == 0)
		pwd_process();
	else if (ft_strcmp(token->cmd, "export") == 0)
		export_process(token, &(*shell)->env);
	else if (ft_strcmp(token->cmd, "unset") == 0)
		unset_process(token, &(*shell)->env);
	else if (ft_strcmp(token->cmd, "env") == 0)
		env_process((*shell)->env);
	return;
}

int		is_builtin(t_token *token)
{
	if (ft_strcmp(token->cmd, "exit") == 0)
		return (TRUE);
	else if (ft_strcmp(token->cmd, "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(token->cmd, "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(token->cmd, "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(token->cmd, "export") == 0)
		return (TRUE);
	else if (ft_strcmp(token->cmd, "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(token->cmd, "env") == 0)
		return (TRUE);
	return (FALSE);
}

void	execution(t_token *token, t_shell **shell)
{
	if (is_builtin(token) == FALSE)
		exec_cmd(token, shell);
	else
		exec_builtin(token, shell);
}
