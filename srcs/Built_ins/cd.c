/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:28:32 by allanganoun       #+#    #+#             */
/*   Updated: 2021/08/02 17:47:30 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_cd_errors(t_token *token)
{
	write(2, "Minishell: ", 11);
	write(2, token->arg[0], ft_strlen(token->arg[0]));
	write(2, ": No such file or directory\n", 28);
}

void	replace_current_dir(char **env_str)
{
	char *tmp;

	tmp = ft_strjoin("PWD=", getcwd(NULL, 0));
	safe_free(env_str);
	*env_str = tmp;
}

void	cd_process(t_token *token, char ***env)
{
	int i;

	i = 0;
	if (*token->arg)
	{
		if (ft_strcmp(*token->arg, "~") == 0)
		{
			if (chdir(ft_strjoin("/Users/", my_getenv("USER", *env))) != 0)
				write_cd_errors(token);
		}
		else if (chdir(token->arg[0]) != 0)
			write_cd_errors(token);
	}
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], "PWD=", 4) == 0)
			replace_current_dir(&((*env)[i]));
		i++;
	}

}
