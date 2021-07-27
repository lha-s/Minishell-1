/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musoufi <musoufi@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 08:54:52 by alganoun          #+#    #+#             */
/*   Updated: 2021/07/27 20:48:29 by musoufi          ###   ########lyon.fr   */
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

int wret;

typedef struct		s_shell
{
	char			**env;
}					t_shell;

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
int			echo_process(t_token *token, char **env);
int			bash_process(/*t_cmd **cmd,*/ char **tab);
int			export_process(t_token *token, char ***env);
int			unset_process(t_token *token, char ***env);
int			env_process(char **env);
int			word_count(char *str);
int			write_exec_errors();
int			init_struct(t_token **token);
void		free_tab(char ***tab);
void		safe_free(char **str);
t_token		*token_last(t_token *token);
void		token_add_back(t_token **atoken, t_token **new);
t_token		*token_new();
int			space_into_dot(char **str);
int			coma_into_dot(char **str);
void		option_finder(char *str, t_token **token);
int			operator_finder(char *str, t_token **token);
void		arg_finder(char *str, t_token **token);
int			tablen(char **tab);
int			reallocate_tab(char ***tab, char *str);
void		free_struct(t_token **token);
int			exit_free(t_token **token, char **line);
void		quote_remover(char **str);
void		token_cleaning(t_token **token);
int			write_variable(char *str, char c, char **env);

char 		*my_getenv(char *name, char **env);
int			variable_len(char *str);
char		**value_name_tab(char **env);
void		get_variable_value(char **str, char **env);
int			check_name(char *name);
int 		run_process(t_token *token, t_shell **shell);
int			fork_process(t_token *token, t_shell **shell, int fdd);
void		execution(t_token *token, t_shell **shell);
void		exec_cmd(t_token *token, t_shell **shell);
void		exit_prog(t_token **token, int exit_message);
void		exit_status(t_token **token, pid_t pid);

#endif
