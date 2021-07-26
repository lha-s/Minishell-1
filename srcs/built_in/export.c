/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 12:34:34 by allanganoun       #+#    #+#             */
/*   Updated: 2021/07/26 17:11:13 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_name(char *name)
{
	int i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '=' && (i > 0))
			return (1);
		i++;
	}
	return (0);
}

int		export_process(t_token *token, char ***env)
{
	int i;
	char *str;

	i = 0;
	while (token->arg[i] != NULL)
	{
		str = ft_strdup(token->arg[i]);
		if (check_name(str) == 1)
		{
			get_variable_value(&str, *env);
			reallocate_tab(env, str);
		}
		i++;
	}
	return (TRUE);
}
