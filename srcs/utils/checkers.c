/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 16:37:55 by allanganoun       #+#    #+#             */
/*   Updated: 2021/07/31 20:33:29 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		option_checker(t_token *token)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (token->option && token->option[i] != NULL)
	{
		while (token->option[i][j])
		{
			if (token->option[i][j] == '.' || token->option[i][j] == ';'
				|| token->option[i][j] == '\\')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		arg_checker(t_token *token)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (token->arg && token->arg[i] != NULL)
	{
		while (token->arg[i][j])
		{
			if (token->arg[i][j] == '.' || token->arg[i][j] == ';'
				|| token->arg[i][j] == '\\')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		cmd_cheker(t_token *token)
{
	int i;

	i = 0;
	while (token->cmd && token->cmd[i])
	{
		if (token->cmd[i] == '.' || token->cmd[i] == ';'
			|| token->cmd[i] == '\\')
			return (1);
		i++;
	}
	return (0);
}

int		token_checker(t_token *token)
{
	if (token)
	{
		if (cmd_cheker(token) == 1 || arg_checker(token) == 1
			|| option_checker(token) == 1)
			return (1);
	}
	return (0);
}
