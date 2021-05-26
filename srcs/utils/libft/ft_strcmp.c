/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:49:08 by alganoun          #+#    #+#             */
/*   Updated: 2021/02/22 16:35:51 by alganoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	i = 0;
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	if (cs1 == NULL)
		return(-cs2[i]);
	else if (cs2 == NULL)
		return(cs1[i]);
	while (cs1[i] && cs2[i] && cs1[i] == cs2[i])
		i++;
	return (cs1[i] - cs2[i]);
}
