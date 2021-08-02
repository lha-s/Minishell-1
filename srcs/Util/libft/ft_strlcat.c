/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alganoun <alganoun@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/05 12:58:55 by alganoun     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 15:50:40 by alganoun    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t dlen;
	size_t slen;

	i = 0;
	j = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen((char *)src);
	if (dlen >= size)
		return (size + slen);
	else
	{
		j = 0;
		i = dlen;
		while (j < (size - dlen - 1) && src[j])
			dst[i++] = src[j++];
		dst[i] = '\0';
		return (dlen + slen);
	}
	return (0);
}
