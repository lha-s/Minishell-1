/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:34:59 by alganoun          #+#    #+#             */
/*   Updated: 2021/05/28 17:04:33 by alganoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		command_parsing(char **line, t_token **token_list)
{
	(*token_list)->cmd = get_next_word(*line);
	if ((*token_list)->cmd == NULL)
		return (-1);
	*line += ft_strlen((*token_list)->cmd);
	return (0);
}

int		option_parsing(char **line, t_token **token_list)
{
	char *word;
	int found;

	found = 1;
	while (found == 1)
	{
		found = 0;
		word = get_next_word(*line);
		if (word == NULL)
			return (-1);
		if (is_option(word) == 1)
			found = 1;
		if (found == 1)
		{
			(*token_list)->option = ft_strjoin((*token_list)->option, word);
			if ((*token_list)->option == NULL)
				return (-1);
		}
		*line += ft_strlen(word);
		free(word);
	}
	return (0);
}

int		argument_parsing(char **line, t_token **token_list)
{
	char *word;

	word = get_next_word(*line);
	while (word[0] != '\0')
	{
		(*token_list)->arg = ft_strjoin((*token_list)->arg, word);
		if ((*token_list)->arg == NULL)
			return (-1);
		*line += ft_strlen((*token_list)->cmd);
		free (word);
		word = get_next_word(*line);
	}
	return (0);
}
