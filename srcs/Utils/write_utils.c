/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:00:24 by alganoun          #+#    #+#             */
/*   Updated: 2021/08/12 13:34:42 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

ssize_t		write_output(char *str)
{
	return ((write(1, str, ft_strlen(str))) + (write(1, "\n", 1)));
}

int		write_errors(int option, char *str)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	if (option == 1)
	{
		ft_putendl_fd("use of unsupported character", STDERR_FILENO);
	}
	else if (option == 2)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		return (0);
	}
	else if (option == 3)
		ft_putendl_fd("Quotes open, close them", STDERR_FILENO);
	else if (option == 4)
		ft_putendl_fd("PATH error", STDERR_FILENO);
	else if (option == 5)
		ft_putendl_fd("redirection error detected", STDERR_FILENO);
	return (-1);
}

int	fd_write_errors(char *cmd)
{
	DIR	*dir;
	int	fd;
	int	ret;

	fd = open(cmd, O_WRONLY);
	dir = opendir(cmd);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (ft_strchr(cmd, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else if (fd == -1 && dir == NULL)
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	else if (fd == -1 && dir != NULL)
		ft_putendl_fd(": is a directory", STDERR_FILENO);
	else if (fd != -1 && dir == NULL)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	if (ft_strchr(cmd, '/') == NULL || (fd == -1 && dir == NULL))
		ret = 127;
	else
		ret = 126;
	if (dir)
		closedir(dir);
	if (fd > 0)
		close(fd);
	return (ret);
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
