/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alganoun <alganoun@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 13:30:33 by alganoun     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/23 15:31:04 by alganoun    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*t;
	const unsigned char *u;

	i = 0;
	t = dst;
	u = src;
	while (i < n && u[i] != (unsigned char)c)
	{
		t[i] = u[i];
		i++;
	}
	if (u[i] == (unsigned char)c)
	{
		t[i] = u[i];
		t = &t[i + 1];
		dst = t;
		return (dst);
	}
	return (NULL);
}
