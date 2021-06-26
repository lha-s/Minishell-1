/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:06:00 by alganoun          #+#    #+#             */
/*   Updated: 2021/06/24 16:55:37 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	safe_free(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

void	free_tab(char ***tab)
{
	int i;

	i = 0;
	if (*tab != NULL)
	{
		while ((*tab)[i] != NULL)
		{
			safe_free(&(*tab)[i]);
			i++;
		}
		free(*tab);
		*tab = NULL;
	}
}

void	free_struct(t_token **token)
{
	safe_free(&(*token)->cmd);
	free_tab(&(*token)->option);
	free_tab(&(*token)->arg);
	(*token)->next = NULL;
}
