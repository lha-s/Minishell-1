/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 11:34:59 by alganoun          #+#    #+#             */
/*   Updated: 2021/03/03 13:43:15 by musoufi          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/*int		input_parsing(char *line)
{
	//int i;
	//char *command;
//
	//i = 0;
	//command = NULL;
	//while (line[i])
	//{
	//	command = get_next_word(&(line[i]));
	//	if (input_process(command) == -1)
	//		return (-1);
	//	i = ft_strlen(command) - 1;
	//}
	return (0);
}*/

int		execute_command(t_cmd **cmd)
{
	int i;

	i = 0;
	while((*cmd)->cmdline[i] != NULL)
	{
		//if (ft_strcmp(command, "echo") == 0)
			//return(echo_process());
		//else if (ft_strcmp(command, "cd") == 0)
			//return(cd_process());
		if (ft_strcmp((*cmd)->cmdline[i], "pwd") == 0)
			return (pwd_process(/*cmd*/));
		//else if (ft_strcmp(command, "export") == 0)
		//	return (export_process());
		//else if (ft_strcmp(command, "unset") == 0)
		//	return (unset_process());
		//else if (ft_strcmp(command, "env") == 0)
		//	return (env_process());
		else if (ft_strcmp((*cmd)->cmdline[i], "bash") == 0)
			return (bash_process(/*cmd,*/ &((*cmd)->cmdline[i])));
		else if (ft_strlen((*cmd)->cmdline[i]) > 0)
			return (write_errors(2, (*cmd)->cmdline[i]));
		i++;
	}
	return(0);
}
