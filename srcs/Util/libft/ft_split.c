/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:25:55 by alganoun          #+#    #+#             */
/*   Updated: 2021/06/29 15:37:54 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

static char			**ft_clear(char ** tab, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (tab);
}

static int			ft_check_sep(char s, char c)
{
	if (c == s)
		return (1);
	else
		return (0);
}

static unsigned int	number_of_words(char const *s, char c)
{
	int i;
	int words_nb;
	int in_word;

	in_word = 0;
	words_nb = 0;
	i = 0;
	while (s[i])
	{
		if (ft_check_sep(s[i], c) == 0)
		{
			if (in_word == 0)
			{
				words_nb++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		i++;
	}
	return (words_nb);
}

static char			*ft_alloc_words(char const *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && ft_check_sep(s[i], c) == 0)
		i++;
	if (!(word = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i] && ft_check_sep(s[i], c) == 0)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char				**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**tab;

	if (s == NULL)
		return (NULL);
	if (!(tab = malloc(sizeof(char *) * (number_of_words(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (ft_check_sep(s[i], c) == 1)
			i++;
		if (s[i] && ft_check_sep(s[i], c) == 0)
		{
			if (!(tab[j] = ft_alloc_words(&s[i], c)))
				return (ft_clear(tab, j));
			j++;
			while (s[i] && ft_check_sep(s[i], c) == 0)
				i++;
		}
	}
	tab[j] = NULL;
	return (tab);
}
