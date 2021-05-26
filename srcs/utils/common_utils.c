/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 08:00:40 by alganoun          #+#    #+#             */
/*   Updated: 2021/03/08 17:06:11 by allanganoun      ###   ########.fr       */
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

int command_identifier(char *str)
{
	int i;

	i = 0;
	if 
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