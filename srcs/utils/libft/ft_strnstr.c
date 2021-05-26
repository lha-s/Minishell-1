/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alganoun <alganoun@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/10 11:45:17 by alganoun     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/17 14:27:41 by alganoun    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t check;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		check = i;
		while (needle[j] && (haystack[i] == needle[j]) && (i < len))
		{
			if (needle[j + 1] == '\0')
			{
				haystack = &haystack[check];
				return ((char *)haystack);
			}
			i++;
			j++;
		}
		i = check;
		i++;
	}
	return (NULL);
}
