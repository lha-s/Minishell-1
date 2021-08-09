/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 01:40:44 by allanganoun       #+#    #+#             */
/*   Updated: 2021/08/09 01:42:15 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dquote_missing_space(char **str, char **tmp, int *i, int *j)
{
	(*tmp)[(*j)++] = (*str)[(*i)++];
	while ((*str)[*i] && (*str)[*i] != '"')
	{
		if ((*str)[*i] == '\\' && (*str)[(*i) + 1] == '"')
			(*tmp)[(*j)++] = (*str)[(*i)++];
		(*tmp)[(*j)++] = (*str)[(*i)++];
	}
	(*tmp)[(*j)++] = (*str)[(*i)++];
}

void	squote_missing_space(char **str, char **tmp, int *i, int *j)
{
	(*tmp)[(*j)++] = (*str)[(*i)++];
	while ((*str)[*i] && (*str)[*i] != '\'')
	{
		if ((*str)[*i] == '\\' && (*str)[(*i) + 1] == '\'')
			(*tmp)[(*j)++] = (*str)[(*i)++];
		(*tmp)[(*j)++] = (*str)[(*i)++];
	}
	(*tmp)[(*j)++] = (*str)[(*i)++];
}

void	dchev_missing_space(char **str, char **tmp, int *i, int *j)
{
	(*tmp)[(*j)++] = ' ';
	(*tmp)[(*j)++] = (*str)[(*i)++];
	(*tmp)[(*j)++] = (*str)[(*i)++];
	(*tmp)[(*j)++] = ' ';
}

void	pipechev_missing_space(char **str, char **tmp, int *i, int *j)
{
	(*tmp)[(*j)++] = ' ';
	(*tmp)[(*j)++] = (*str)[(*i)++];
	(*tmp)[(*j)++] = ' ';
}
