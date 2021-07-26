/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 12:42:11 by allanganoun       #+#    #+#             */
/*   Updated: 2021/07/25 23:08:53 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int		echo_process(t_token *token, char **env)
// {
	// int i;
	// int j;
	// char quote;
//
	// i = 0;
	// quote = '\0';
	// while (token->arg[i] != NULL)
	// {
		// j = 0;
		// if (token->arg[i][0] == '"' || token->arg[i][0] == '\'')
			// quote = token->arg[i][0];
		// while (token->arg[i][j])
		// {
			// if (token->arg[i][j] == '$')
				// j = write_variable(&(token->arg[i][j + 1]), quote, env) + j + 1;
			// write (1, &(token->arg[i][j]), 1);
			// j++;
		// }
		// if (token->arg[i + 1] != NULL)
			// write(1, " ", 1);
		// i++;
	// }
	// if (token->option == NULL)
		// write(1, "\n", 1);
	// return (TRUE);
// }

int		echo_process(t_token *token, char **env)
{
	int i;
	int j;
	char *str;

	i = 0;
	j = 0;
	while (token->arg && token->arg[i] != NULL)
	{
		str = ft_strdup(token->arg[i]);
		get_variable_value(&str, env);
		write (1, str, ft_strlen(str));
		if (token->arg[i + 1] != NULL)
			write (1, " ", 1);
		safe_free(&str);
		i++;
	}
	if (token->option)
	{
		while (ft_strcmp(token->option[j], "-n") != 0)
			j++;
		if (token->option[j] == NULL)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
	return (TRUE);
}
