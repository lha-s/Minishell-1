/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 08:37:43 by alganoun          #+#    #+#             */
/*   Updated: 2021/07/30 18:21:58 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printf_all(t_token *token) // Il faut supprimer cette fonction avant le rendu
{
	while (token != NULL)
	{
		printf("CMD : %s\n", token->cmd);
		printf("OPERATOR : %s\n", token->operator);
		if (token->option != NULL)
			for (int i = 0 ; token->option[i] != NULL ; i++)
				printf("OPTION = %s\n", token->option[i]);
		else
			printf("OPTION = NULL\n");
		if (token->arg != NULL)
			for (int i = 0 ; token->arg[i] != NULL ; i++)
				printf("ARG = %s\n", token->arg[i]);
		else
			printf("arg = NULL\n");
		if (token->in)
			printf("IN = %d\n", token->in);
		else
			printf("IN = NULL\n");
		if (token->out)
			printf("OUT = %d\n", token->out);
		else
			printf("OUT = NULL\n");
		printf("\n");
		token = token->next;
	}
}

void	init_shell(char **old_env, t_shell **shell)
{
	int i;
	int lenght;

	i = 0;
	lenght = tablen(old_env);
	(*shell) = malloc(sizeof(t_shell));
	(*shell)->env = malloc((lenght + 1) * sizeof(char *));
	while (old_env[i] != NULL)
	{
		(*shell)->env[i] = ft_strdup(old_env[i]);
		i++;
	}
	(*shell)->env[i] = NULL;
}

int		input_process2(char **pre_token, t_token **token)
{
	int i;
	t_token *new;

	i = 1;
	(*token)->cmd = pre_token[0];
	quote_remover(&((*token)->cmd));
	while (pre_token && pre_token[i] != NULL)
	{
		quote_remover(&(pre_token[i]));
		if (operator_finder(pre_token[i], token) == 1)
		{
			i++;
			init_struct(&new);
			new->next = (*token)->next->next;
			(*token)->next->next = new;
			new->cmd = pre_token[i];
			*token = new;
		}
		else
		{
			option_finder(pre_token[i], token);
			arg_finder(pre_token[i], token);
		}
		i++;
	}
	return (0);
}

int		input_process(char *line, t_token **token)
{
	int i;
	int j;

	i = 0;
	char **pre_token;
	(void)token;
	j = 0;
	if (space_into_dot(&line) == -1)
		return (-1);
	pre_token = ft_split(line, 13);
	input_process2(pre_token, token);
	return (0);
}

int		parsing(char *line, t_token **token_list)
{
	int		i;
	t_token	*new;
	i = 0;

	if (*token_list != NULL)
	free_struct(token_list);
	init_struct(&new);
	token_add_back(token_list, &new);
	if (input_process(line, &new) == -1)
		return (-1);
	return(0);
}

void	piping(t_token **token)
{
	t_token *tmpA;
	t_token *tmpB;

	if ((*token)->next)
	{
		tmpA = (*token);
		tmpB = (*token)->next;
		while (tmpB->next)
		{
			if (tmpB->operator && strncmp(tmpB->operator, "|", 1) == 0)
			{
				tmpA->out = 1;
				tmpB->next->in = 1;
			}
			tmpA = tmpA->next;
			tmpB = tmpB->next;
		}
	}
}

int		minishell(t_shell **shell)
{
	int ret;
	char *line;
	t_token *token;

	ret = 1;
	token = NULL;
	line = NULL;
	while(ret != 0)
	{
		get_next_input(&line);
		if (parsing(line, &token) != -1 && token != NULL)
		{
			piping(&token);
			printf_all(token);
			ret = run_process(token, shell);
			free_struct(&token);
		}
	}
	//exit_status(&token);
	safe_free(&line);
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_shell	*shell;
	init_shell(env, &shell);
	if (display_txt("banner.txt") == -1)
		return (-1);
	if (minishell(&shell) == -1)
		return (-1); // imprimer un message d'erreur ici
	return (0);
}
