/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alganoun <alganoun@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 14:45:38 by alganoun     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/23 16:02:55 by alganoun    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkset(const char *set, char c)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	size_t			end;
	char			*tab;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = (ft_strlen(s1) - 1);
	while (ft_checkset(set, s1[start]) == 1)
		start++;
	while (ft_checkset(set, s1[end]) == 1 && end >= start)
		end--;
	tab = ft_substr(s1, start, (end - start + 1));
	return (tab);
}
