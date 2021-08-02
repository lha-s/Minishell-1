/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:19:07 by alganoun          #+#    #+#             */
/*   Updated: 2021/08/02 17:00:27 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *prompt(void)
{
	char *tmp;
	char *line;
	size_t len;

	line = ft_strjoin("[", getenv("USER"));
	line = ft_strjoin(line, "]");
	tmp = getcwd(NULL, 0);
	len = ft_strlen(tmp);
	while (tmp[len] != '/')
		len--;
	tmp = &tmp[len + 1];
	line = ft_strjoin(line, " ");
	line = ft_strjoin(line, tmp);
	line = ft_strjoin(line, " • ");
	return (line);
}

void	get_next_input(char **line)
{
	if (*line != NULL)
	{
		safe_free(line);
		*line = NULL;
	}
	*line = readline(prompt());
	add_history(*line);
}
