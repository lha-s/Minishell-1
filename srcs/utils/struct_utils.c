/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 08:53:22 by alganoun          #+#    #+#             */
/*   Updated: 2021/07/01 11:14:36 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		init_struct(t_token **token)
{
	*token = (t_token *)malloc(1 * sizeof(t_token));
	if (!(*token))
		return (-1);
	**token = (t_token){
		.cmd = NULL,
		.option = NULL,
		.arg = NULL,
		.operator = NULL,
		.next = NULL,
		.in = 0,
		.out = 0,
		.pid_index = 0,
		.pids = {0}
	};
	return (0);
}

t_token		*token_last(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

void	token_add_back(t_token **atoken, t_token **new)
{
	t_token *last;

	if (*atoken == NULL)
		*atoken = *new;
	else
	{
		last = token_last(*atoken);
		last->next = *new;
		(*new)->next = NULL;
	}
}

t_token	*token_new()
{
	t_token *token;

	init_struct(&token);
	return (token);
}
