/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alganoun <alganoun@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 12:03:27 by alganoun     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/21 17:36:30 by alganoun    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*t;
	const unsigned char	*u;

	i = 0;
	t = dst;
	u = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		t[i] = u[i];
		i++;
	}
	return (t);
}
