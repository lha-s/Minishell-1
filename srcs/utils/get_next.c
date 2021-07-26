/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:19:07 by alganoun          #+#    #+#             */
/*   Updated: 2021/07/25 22:34:40 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		get_next_line(int fd, char **line)
{
	int		i;
	int		l;
	int		r;
	char 	c;
	char	*tmp;

	l = 1;
	r = 0;
	if(!(*line = malloc(1)))
		return (-1);
	(*line)[0] = 0;
	while ((r = read(fd, &c, 1)) && l++ && c != '\n')
	{
		if(!(tmp = malloc(l)))
		{
			free(*line);
			return (0);
		}
		i = -1;
		while (++i < l - 2)
			tmp[i] = (*line)[i];
		tmp[i] = c;
		tmp[i + 1] = '\0';
		free(*line);
		*line = tmp;
	}
	return (r);
}

void	get_next_input(char **line)
{
	//if (*line != NULL)
	//	safe_free(line);
	*line = readline("[minishell-1.0$ ");
	add_history(*line);
}
