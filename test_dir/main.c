/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 08:53:55 by alganoun          #+#    #+#             */
/*   Updated: 2021/07/22 17:11:41 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


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

static int			ft_check_sep(char s, char *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == s)
			return (1);
		i++;
	}
	return(0);
}

static unsigned int	number_of_words(char const *s, char *charset)
{
	int i;
	int words_nb;
	int in_word;

	in_word = 0;
	words_nb = 0;
	i = 0;
	while (s[i])
	{
		if (ft_check_sep(s[i], charset) == 0)
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

static char			*ft_alloc_words(char const *s, char *charset)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && ft_check_sep(s[i], charset) == 0)
		i++;
	if (!(word = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (s[i] && ft_check_sep(s[i], charset) == 0)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char				**ft_split2(char const *s, char *charset)
{
	int		i;
	int		j;
	char	**tab;

	if (s == NULL)
		return (NULL);
	if (!(tab = malloc(sizeof(char *) * (number_of_words(s, charset) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (ft_check_sep(s[i], charset) == 1)
			i++;
		if (s[i] && ft_check_sep(s[i], charset) == 0)
		{
			if (!(tab[j] = ft_alloc_words(&s[i], charset)))
				return (ft_clear(tab, j));
			j++;
			while (s[i] && ft_check_sep(s[i], charset) == 0)
				i++;
		}
	}
	tab[j] = NULL;
	return (tab);
}


int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	int i;

	i = 0;

	char str[]="coucoujesuisunecommamde&PATH-coucouc&VAR";
	char **tab = ft_split2(str, "$ !\"#$%%&*+,-.");
	while (tab[i] != NULL)
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
}
