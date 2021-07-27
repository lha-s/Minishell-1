/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:06:00 by alganoun          #+#    #+#             */
/*   Updated: 2021/07/27 01:09:47 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	safe_free(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

void	free_tab(char ***tab)
{
	int i;

	i = 0;
	if (*tab != NULL)
	{
		while ((*tab)[i] != NULL)
		{
			safe_free(&((*tab)[i]));
			i++;
		}
		free(*tab);
		*tab = NULL;
	}
}

void	free_struct(t_token **token)
{
	t_token *next;
	while ((*token)->next != NULL)
	{
		safe_free(&((*token))->cmd);
		free_tab(&((*token))->option);
		free_tab(&((*token))->arg);
		next = (*token)->next;
		free(*token);
		*token = NULL;
		*token = next;
	}
	safe_free(&(*token)->cmd);
	free_tab(&(*token)->option);
	free_tab(&(*token)->arg);
	free((*token));
	*token = NULL;
}

int		exit_free(t_token **token, char **line)
{
	free_struct(token);
	safe_free(line);
	return (-1);
}

void	exit_prog(t_token **token, int exit_message)
{
	if (token)
		free_struct(token);
	if (exit_message == TRUE)
		ft_putstr_fd("Bash: exit\n", STDERR_FILENO);
	exit(wret);
}