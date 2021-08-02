/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alganoun <alganoun@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 16:24:45 by alganoun     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 15:12:22 by alganoun    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*t;
	const unsigned char	*u;

	t = dst;
	u = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (u < t)
	{
		while (len != 0)
		{
			t[len - 1] = u[len - 1];
			len--;
		}
	}
	else if (t < u)
		ft_memcpy(dst, src, len);
	return (dst);
}
