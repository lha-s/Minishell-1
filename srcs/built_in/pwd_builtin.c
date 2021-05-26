/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:29:39 by alganoun          #+#    #+#             */
/*   Updated: 2021/03/03 13:41:07 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		pwd_process(/*t_cmd **cmd*/)
{
	char *buffer;

	buffer = (char *)malloc(PATH_MAX);
	if (getcwd(buffer, PATH_MAX) != NULL)
		write_output(buffer);
	free(buffer);
	return (0);
}
