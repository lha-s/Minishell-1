/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 08:53:22 by alganoun          #+#    #+#             */
/*   Updated: 2021/05/22 14:25:12 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		init_struct(t_token **token)
{
	if (!(*token = (t_token *)malloc(1 * sizeof(t_token))))
		return (-1);
	(*token)->cmd = NULL;
	(*token)->option = NULL;
	(*token)->arg = NULL;
	(*token)->next = NULL;
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

void	token_add_back(t_token **atoken, t_token *new)
{
	t_token *last;

	if (*atoken == NULL)
	{
		new->next = NULL;
		*atoken = new;
	}
	else
	{
		last = token_last(*atoken);
		last->next = new;
		new->next = NULL;
	}
}

t_token	*token_new(char *content)
{
	t_token *token;

	init_struct(&token);
	return (token);
}
