/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:34:34 by allanganoun       #+#    #+#             */
/*   Updated: 2021/07/22 21:06:30 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_name(char *name)
{
	int i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '=' && i < 0)
			return (1);
		i++;
	}
	return (0);
}

void	set_variable(char *name)
{
	int i;
	char *begin;
	char *variable;

	i = 0;
	while (name[i] && name[i] !=  '=')
		i++;
	begin = malloc(i + 2);
	i = 0;
	while (name[i] && name[i] !=  '=')
	{
		begin[i] = name[i];
		i++;
	}
	begin[i++] = '=';
	begin[i] = '\0';
	variable = variable

}

int		export(char ***env, t_token *token)
{
	int i;
	int j;

	i = 0;
	while (token->arg[i] != NULL)
	{
		j = 0;
		if (check_name(token->arg[i]) == 1)
		{
			while (token->arg[i][j])
			{

				j++;
			}
			reallocate_tab(env, token->arg[i]);
		}
		i++;
	}
	return (TRUE);
}
