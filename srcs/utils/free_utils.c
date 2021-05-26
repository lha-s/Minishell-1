/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:06:00 by alganoun          #+#    #+#             */
/*   Updated: 2021/02/23 16:37:36 by alganoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	safe_free(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

void	free_tab(char ***tab, int count)
{
	int i;

	i = 0;
	while (count != 0)
	{
		safe_free(&(*tab)[i]);
		i++;
		count--;
	}
	free(*tab);
	*tab = NULL;
}
