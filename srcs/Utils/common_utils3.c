/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:07:55 by allanganoun       #+#    #+#             */
/*   Updated: 2021/08/09 09:52:32 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_missing_space2(char **str, int count)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	tmp = ft_malloc(ft_strlen(*str) + (count * 2) + 1);
	while ((*str)[i])
	{
		if ((*str)[i] == '"')
			dquote_missing_space(str, &tmp, &i, &j);
		else if ((*str)[i] == '\'')
			squote_missing_space(str, &tmp, &i, &j);
		else if ((*str)[i] == '|' || ((*str)[i] == '>' && (*str)[i + 1] != '>')
			|| ((*str)[i] == '<' && (*str)[i + 1] != '<'))
			pipechev_missing_space(str, &tmp, &i, &j);
		else if (((*str)[i] == '>' && (*str)[i + 1] == '>')
			|| ((*str)[i] == '<' && (*str)[i + 1] == '<'))
			dchev_missing_space(str, &tmp, &i, &j);
		else
			tmp[j++] = (*str)[i++];
	}
	tmp[j] = '\0';
	*str = tmp;
}

int		add_missing_space(char **str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '"')
			i = double_quote(*str, i);
		else if ((*str)[i] == '\'')
			i = simple_quote(*str, i) ;
		if (i == -1)
			return (write_errors(BAD_QUOTES, NULL));
		else if ((*str)[i] == '|' || ((*str)[i] == '>' && (*str)[i + 1] != '>')
			|| ((*str)[i] == '<' && (*str)[i + 1] != '<'))
		{
			if ((*str)[i + 1] == '\0')
				return (write_errors(REDIR_ERROR, NULL));
			count++;
		}
		i++;
	}
	add_missing_space2(str, count);
	return (0);
}
