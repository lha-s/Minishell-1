/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:19:07 by alganoun          #+#    #+#             */
/*   Updated: 2021/06/23 13:21:17 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//char	*get_next_word(char *line)
//{
//	int i;
//	char *word;
//
//	i = 0;
//	ft_rm_whitespace(&line);
//	if (line[0] == '"')
//		while (line[i] && line[i] != '"')
//			i++;
//	else if (line[0] == '\'')
//		while (line[i] && line[i] != '\'')
//			i++;
//	else
//		while (line[i] && (line[i] <= 9 || line[i] >= 13) && line[i] != 32)
//			i++;
//	if (!(word = malloc(i + 1)))
//		return (NULL);
//	ft_strlcpy(word, line, i + 1);
//	return (word);
//}

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

int		get_next_input(char **line)
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
	while ((r = read(0, &c, 1)) && l++ && c != '\n')
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
