/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 08:00:40 by alganoun          #+#    #+#             */
/*   Updated: 2021/08/02 21:24:25 by allanganoun      ###   ########.fr       */
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

int		variable_len(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			while (str[i] && (str[i] < 32 || str[i] > 47)
				&& (str[i] < 58 || str[i] > 64) )
			{
				count++;
				i++;
			}
			return (count);
		}
		i++;
	}
	return (count);
}

int		display_txt(char *str)
{
	int fd;
	int ret;
	char *line;
	ret = 1;

	fd = open(str, O_RDONLY);
	if (fd > 0)
	{
		while(ret > 0)
		{
			ret = get_next_line(fd, &line);
			write_output(line);
			free(line);
		}
		ret = get_next_line(fd, &line);
		write_output(line);
		free(line);
	}
	if (ret != 0)
		return (write_errors(1, str));
	return (0);
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
