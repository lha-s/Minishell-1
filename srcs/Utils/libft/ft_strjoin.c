/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:03:46 by alganoun          #+#    #+#             */
/*   Updated: 2021/08/09 09:43:04 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		maxlen;
	char	*dst;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return (NULL);
	maxlen = (int)ft_strlen(s1) + (int)ft_strlen(s2);
	if (!(dst = (char *)ft_malloc((maxlen + 1) * sizeof(char))))
		return (NULL);
	while (j < (int)ft_strlen(s1))
		dst[i++] = s1[j++];
	j = 0;
	while (j < (int)ft_strlen(s2))
		dst[i++] = s2[j++];
	dst[i] = '\0';
	return (dst);
}
