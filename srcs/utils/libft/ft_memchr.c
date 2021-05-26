/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alganoun <alganoun@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 10:53:31 by alganoun     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/24 15:25:54 by alganoun    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*t;
	size_t				i;

	t = s;
	i = 0;
	while (i < n)
	{
		if (*t == (unsigned char)c)
			return ((char *)t);
		i++;
		t++;
	}
	return (NULL);
}
