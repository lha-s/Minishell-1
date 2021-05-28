/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 08:37:43 by alganoun          #+#    #+#             */
/*   Updated: 2021/05/28 17:11:28 by alganoun         ###   ########lyon.fr   */
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

int		input_process(char **tab, t_token **token_list)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{

		i++;
	}
	return (0);
}

int		parsing(char *line, t_token **token_list)
{
	int		i;
	char	**tab;

	i = 0;
	// fonction de gestion d'erreurs
	if (!(tab = ft_split(line, ';')) == NULL)
		return (write_errors(3, NULL));
	input_process(tab, token_list);
	return(0);
}

int		main(/*int argc, char **argv, char **data*/)
{
	int ret;
	//int	fd;
	char *line;
	t_token *token;

	ret = 1;
	if(init_struct(&token) == -1)
		return (write_errors(3, NULL));
	if (display_txt("banner.txt") == -1)
		return (-1);
	while(ret != 0)
	{
		write(1, "[minishell-1.0$ ", 16);
		get_next_input(&line);
		if (parsing(line, &token) == -1)
			return(-1);
		//execution_commandes(envcopy)
		safe_free(&line);
	}
	safe_free(&line);
	safe_free((char **)&token);
	return (0);
}
