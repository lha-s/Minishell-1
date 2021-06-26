/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:34:59 by alganoun          #+#    #+#             */
/*   Updated: 2021/06/26 17:40:34 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	option_finder(char *str, t_token **token)
{
	int i;

	i = 0;
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

void	arg_finder(char *str, t_token **token)
{
	int i;

	i = 0;
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
