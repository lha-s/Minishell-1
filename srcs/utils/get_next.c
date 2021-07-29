/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:19:07 by alganoun          #+#    #+#             */
/*   Updated: 2021/07/29 20:20:10 by allanganoun      ###   ########.fr       */
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

char	*prompt(void)
{
	char	*tmp;
	char	*line;
	size_t	len;

	line = ft_strjoin("\e[1;34m(", getenv("USER"));
	line = ft_strjoin(line, ")\033[0m:");
	tmp = getcwd(NULL, 0);
	len = ft_strlen(tmp);
	while (tmp[len] != '/')
		len--;
	tmp = &tmp[len + 1];
	line = ft_strjoin(line, "\033[32;1m ");
	line = ft_strjoin(line, tmp);
	line = ft_strjoin(line, "$\e[0m ");
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
