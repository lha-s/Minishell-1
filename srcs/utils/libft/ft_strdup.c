/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alganoun <alganoun@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/11 08:50:49 by alganoun     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/25 18:44:39 by alganoun    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strdup(const char *s1)
{
	char	*dup;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	if(!(dup = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (s1[i])
	{	
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
