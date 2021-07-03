/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 08:00:40 by alganoun          #+#    #+#             */
/*   Updated: 2021/06/29 17:03:24 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		 tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

int		reallocate_tab(char ***tab, char *str)
{
	char **tmp;
	int i;
	tmp = (char **)malloc(sizeof(char *) * (tablen(*tab) + 2));
	if (!tmp)
		return (-1);
	i = 0;
	while ((*tab)[i] != NULL)
	{
		tmp[i] = (*tab)[i];
		i++;
	}
	tmp[i] = str;
	tmp[i + 1] = NULL;
	free(*tab);
	*tab = tmp;
	return (0);
}

void	space_into_dot(char **str)
{
	int i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
		{
			i++;
			while (((*str)[i] && (*str)[i] != '"')
				&& ((*str)[i] && (*str)[i] != '\''))
				i++;
		}
		else if ((*str)[i] == ' ')
			(*str)[i] = '.';
		i++;
	}
}
