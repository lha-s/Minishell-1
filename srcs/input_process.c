/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:34:59 by alganoun          #+#    #+#             */
/*   Updated: 2021/07/03 17:51:35 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		operator_finder(char *str, t_token **token)
{
	int i;
	t_token *new;

	i = 0;
	if (str !=	NULL)
	{
		if ((str[i] == '|' && str[i + 1] == '\0')
			|| (str[i] == '&' && str[i + 1] == '\0')
			|| (str[i] == '>' && str[i + 1] == '\0')
			|| (str[i] == '<' && str[i + 1] == '\0')
			|| (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '\0')
			|| str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '\0')
		{
			init_struct(&new);
			new->operator = ft_strdup(str);
			new->next = (*token)->next;
			(*token)->next = new;
			return (1);
		}
	}
	return (0);
}

void	option_finder(char *str, t_token **token)
{
	int i;

	i = 0;
	if (str !=	NULL)
	{
		if (str[i] == '"')
			i++;
		if (str[i] == '-' && str[i + 1] != '\0')
		{
			if ((*token)->option == NULL)
			{
				(*token)->option = (char **)malloc(sizeof(char *) * 2);
				(*token)->option[0] = ft_strdup(str);
				(*token)->option[1] = NULL;
			}
			else
				reallocate_tab(&((*token)->option), str);
		}
	}
}

void	arg_finder(char *str, t_token **token)
{
	int i;

	i = 0;
	if (str !=	NULL)
	{
		if (str[i] == '"')
			i++;
		if (str[i] != '-' && str[i + 1] != '\0')
		{
			if ((*token)->arg == NULL)
			{
				(*token)->arg= (char **)malloc(sizeof(char *) * 2);
				(*token)->arg[0] = str;
				(*token)->arg[1] = NULL;
			}
			else
				reallocate_tab(&((*token)->arg), str);
		}
	}
}
