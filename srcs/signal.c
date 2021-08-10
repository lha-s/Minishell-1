/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:46:26 by musoufi           #+#    #+#             */
/*   Updated: 2021/08/10 22:42:11 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	process(int sign_num)
{
	if (!kill(g_sig.pid, sign_num))
	{
		if (sign_num == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			g_sig.exit_status = 131;
		}
		else if (sign_num == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			g_sig.exit_status = 130;
		}
	}
	else if (sign_num == SIGINT)
	{
		ft_putstr_fd("\b\b  ", 1);
		ft_putchar_fd('\n', 1);
		g_sig.exit_status = 1;
		ft_putstr_fd(prompt(), 1);
	}
}

void		sigint_handler(int sign_num)
{
	if ((sign_num == SIGINT || sign_num == SIGQUIT) && g_sig.pid != 0)
		process(sign_num);
	else
	{
		if (sign_num == SIGINT)
		{
			ft_putstr_fd("\b\b  ", 1);
			ft_putchar_fd('\n', 1);
			g_sig.exit_status = 1;
			ft_putstr_fd(prompt(), 1);
		}
		else if (sign_num == SIGQUIT)
			ft_putstr_fd("\b\b  \b\b", 1);
	}
}
