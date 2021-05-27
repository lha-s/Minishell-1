/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:34:59 by alganoun          #+#    #+#             */
/*   Updated: 2021/05/27 15:49:02 by alganoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		command_parsing(char **line, t_token **token_list)
{
	(*token_list)->cmd = get_next_word(line);
	if ((*token_list)->cmd == NULL)
		return (-1);
	*line += ft_strlen((*token_list)->cmd);
	return (0);
}

int		option_parsing()
{

}

int		argument_parsing()
{

}
