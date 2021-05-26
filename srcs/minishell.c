/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 08:37:43 by alganoun          #+#    #+#             */
/*   Updated: 2021/05/22 15:07:28 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		display_txt(char *str)
{
	int fd;
	int ret;
	char *line;
	ret = 1;

	fd = open(str, O_RDONLY);
	printf("%d\n", fd);
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


int		input_process(char *line, t_cmd **cmd)
{
	int			i;
	t_prcess	*current;
	i = 0;
	if (((*cmd)->cmdline = ft_split(line, ';')) == NULL)
		return (write_errors(3, NULL));
	init_cmds(cmd);
	return(0);
}

int		main(/*int argc, char **argv, char **data*/)
{
	int ret;
	//int	fd;
	char *line;
	t_token token;

	ret = 1;
	if(init_struct(&token) == -1)
		return (write_errors(3, NULL));
	if (display_txt("banner.txt") == -1)
		return (-1);
	while(ret != 0)
	{
		write(1, "[minishell-1.0$ ", 16);
		get_next_input(&line);
		if (input_process(line, &token) == -1)
			return(-1);
		safe_free(&line);
	}
	safe_free(&line);
	safe_free((char **)&token);
	return (0);
}
