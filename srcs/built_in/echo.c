/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 12:42:11 by allanganoun       #+#    #+#             */
/*   Updated: 2021/07/12 19:49:33 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		echo_process(t_token *token)
{
	int i;

	i = 0;
	while (token->arg[i] != NULL)
	{
		ft_putendl(1, token->arg[i]);
		if (token->arg[i + 1] != NULL)
			write(1, " ", 1);
	}
	if (token->option == NULL)
		write(1, "\n", 1);
	return (TRUE);
}
