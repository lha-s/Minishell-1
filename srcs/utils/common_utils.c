/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 08:00:40 by alganoun          #+#    #+#             */
/*   Updated: 2021/05/28 14:55:07 by alganoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int		word_count(char *str)
// {
// 	int i;
// 	int nb;
// 	int	found;

// 	i = 0;
// 	nb = 0;
// 	found = 0;
// 	while (str[i])
// 	{
// 		if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
// 			found = 0;
// 		else if (found == 0)
// 		{
// 			nb++;
// 			found = 1;
// 		}
// 		i++;
// 	}
// 	return (nb);
//}

int		is_option(char *str)
{
	if (str[0] == '"' || str[0] == '\'')
		if (str[1] == '-')
			return (1);
	else if (str[0] == '-')
		return (1);
	return (0);
}

int		quotes_checker(char *str) // 	est ce que cette fonction va servir
{
	int	i;

	i = 0;
	if (str[i++] == '"')
	{
		while (str[i])
			i++;
		if (str[1 - 1] != '"')
			return (-1);
	}
	return (0);
}
