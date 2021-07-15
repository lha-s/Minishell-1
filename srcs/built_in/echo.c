/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 12:42:11 by allanganoun       #+#    #+#             */
/*   Updated: 2021/07/15 21:33:00 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		echo_process(t_token *token)
{
	int i;
	int j;
	char quote;

	i = 0;
	quote = '\0';
	while (token->arg[i] != NULL)
	{
		j = 0;
		if (token->arg[i][0] == '"' || token->arg[i][0] == '\'')
			quote = token->arg[i][0];
		while (token->arg[i][j])
		{
			if (token->arg[i][j] == '$')
				j = write_variable(&(token->arg[i][j + 1]), quote) + j + 1;
			write (1, &(token->arg[i][j]), 1);
			j++;
		}
		if (token->arg[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (token->option == NULL)
		write(1, "\n", 1);
	return (TRUE);
}
