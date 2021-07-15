/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 08:54:52 by alganoun          #+#    #+#             */
/*   Updated: 2021/07/15 21:30:44 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0

# define BANNER			1
# define MISSING_FILE	1
# define WRONG_CMD		2
# define BAD_QUOTES		3
# define PATH_ERROR		4
# define BUFFER_SIZE 	1024
# define EXIT_MSG	"\n[Process completed]"

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <string.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../srcs/utils/libft/libft.h"

# define ID_ECHO 0
# define ID_CD 1
# define ID_PWD 2
# define ID_EXPORT 3
# define ID_UNSET 4
# define ID_ENV 5
# define ID_BIN 6

static int num;

typedef struct		s_token
{
	char			*cmd;
	char			**option;
	char			**arg;
	char			*operator;
	struct s_token	*next;
	int 			fd[2];
	char 			in;
	char 			out;
	pid_t 			pids[700];
	int 			pid_index;
}					t_token;

/*------------UTILS---------------*/
int			get_next_line(int fd, char **line);
void		get_next_input(char **line);
int			write_errors(int option, char *str);
size_t		ft_strlen(const char *str);
ssize_t		write_output(char *str);
int			write_exit();
char		*get_next_word(char *line);
int			is_option(char *str);
int			display_txt(char *str);
int			pwd_process();
int			echo_process(t_token *token);
int			bash_process(/*t_cmd **cmd,*/ char **tab);
int			word_count(char *str);
int			write_exec_errors();
int			init_struct(t_token **token);
void		free_tab(char ***tab);
void		safe_free(char **str);
t_token		*token_last(t_token *token);
void		token_add_back(t_token **atoken, t_token **new);
t_token		*token_new();
int			space_into_dot(char **str);
void		option_finder(char *str, t_token **token);
int			operator_finder(char *str, t_token **token);
void		arg_finder(char *str, t_token **token);
int			tablen(char **tab);
int			reallocate_tab(char ***tab, char *str);
void		free_struct(t_token **token);
int			cmd_selector(t_token *token, char **env);
int 		exec_else_(t_token *token, char **env);
int			exit_free(t_token **token, char **line);
void		quote_remover(char **str);
void		token_cleaning(t_token **token);
//void		global_variable_replacement(char **str, char **env);
int			write_variable(char *str, char c);
#endif
