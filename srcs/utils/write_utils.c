/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:00:24 by alganoun          #+#    #+#             */
/*   Updated: 2021/07/27 20:49:52 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

ssize_t		write_output(char *str)
{
	return ((write(1, str, ft_strlen(str))) + (write(1, "\n", 1)));
}

int		write_exit()
{
	write(1, "Bash: exit", 10);
	return (0);
}

int		write_errors(int option, char *str)
{
	write(1, "Bash: ", 7);
	if (option == 1)
	{
		write(1, str, ft_strlen(str));
		write(1, " not found\n", 11);
	}
	else if (option == 2)
	{
		write(1, str, ft_strlen(str));
		write(1, ": command not found\n", 20);
		return (0);
	}
	else if (option == 3)
		write(1, "Quotes open, close them\n", 24);
	else if (option == 4)
		write(1, "PATH error\n", 11);
	return (-1);
}

int		write_variable(char *str, char c, char **env)
{
	int i;
	char *var;
	char *result;

	i = 0;
	while (str[i] != c && str[i] != ' ')
		i++;
	var = malloc(i + 1);
	i = 0;
	while (str[i] != c && str[i] != ' ')
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	result = my_getenv(var, env);
	if (result)
		write (1, result, ft_strlen(result));
	return (i);
}
