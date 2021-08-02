/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alganoun <alganoun@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 13:03:46 by alganoun     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/29 10:05:10 by alganoun    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
	if (!(dst = (char *)malloc((maxlen + 1) * sizeof(char))))
		return (NULL);
	while (j < (int)ft_strlen(s1))
		dst[i++] = s1[j++];
	j = 0;
	while (j < (int)ft_strlen(s2))
		dst[i++] = s2[j++];
	dst[i] = '\0';
	return (dst);
}
