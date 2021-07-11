/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 23:29:18 by allanganoun       #+#    #+#             */
/*   Updated: 2021/07/11 16:00:16 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		pwd_process()
{
	char buff[PATH_MAX];

	if (getcwd(buff, PATH_MAX))
		ft_putendl_fd(buff, 1);
	else
		write_errors(PATH_ERROR, NULL);
	return (TRUE);
}
