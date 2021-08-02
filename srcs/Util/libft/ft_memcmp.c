/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alganoun <alganoun@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 11:15:57 by alganoun     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/23 15:59:28 by alganoun    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*t;
	const unsigned char	*u;

	i = 0;
	t = s1;
	u = s2;
	if (n == 0)
		return (0);
	while (i < (n - 1) && t[i] == u[i])
		i++;
	return (t[i] - u[i]);
}
