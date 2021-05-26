/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_itoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alganoun <alganoun@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/15 10:27:07 by alganoun     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 19:30:22 by alganoun    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static long	ft_digitnb(long n)
{
	int i;

	i = 0;
	if (n <= 9 && n >= 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	long		digitnb;
	long		nb;
	char		*tab;

	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		digitnb = ft_digitnb(nb) + 1;
	}
	else
		digitnb = ft_digitnb(nb);
	if (!(tab = ft_calloc((digitnb + 1), sizeof(char))))
		return (NULL);
	(digitnb == 1) ? (tab[0] = nb + 48) : 0;
	tab[digitnb] = '\0';
	digitnb--;
	while (nb > 0)
	{
		tab[digitnb--] = (nb % 10) + 48;
		nb = nb / 10;
	}
	(n < 0) ? (tab[digitnb] = '-') : 0;
	return (tab);
}
