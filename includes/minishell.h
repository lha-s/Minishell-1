/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allanganoun <allanganoun@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 08:54:52 by alganoun          #+#    #+#             */
/*   Updated: 2021/06/26 17:29:29 by allanganoun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BANNER			1
# define MISSING_FILE	1
# define WRONG_CMD		2
# define BUFFER_SIZE 	1024
# define EXIT_MSG	"\n[Process completed]"

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <string.h>
# include "../srcs/utils/libft/libft.h"

# define ID_ECHO 0
# define ID_CD 1
# define ID_PWD 2
# define ID_EXPORT 3
# define ID_UNSET 4
# define ID_ENV 5
# define ID_BIN 6

typedef struct		s_token
{
	char			*cmd;
	char			**option;
	char			**arg;
	struct s_token	*next;
}					t_token;

/*------------UTILS---------------*/
int			get_next_line(int fd, char **line);
int			get_next_input(char **line);
int			write_errors(int option, char *str);
size_t		ft_strlen(const char *str);
ssize_t		write_output(char *str);
char		*get_next_word(char *line);
int			is_option(char *str);
int			display_txt(char *str);
int			pwd_process(/*t_cmd **cmd*/);
int			bash_process(/*t_cmd **cmd,*/ char **tab);
int			word_count(char *str);
int			write_exec_errors();
int			init_struct(t_token **token);
void		free_tab(char ***tab);
void		safe_free(char **str);
t_token		*token_last(t_token *token);
void		token_add_back(t_token **atoken, t_token **new);
t_token		*token_new();
void		space_into_dot(char **str);
int			input_process2(char **pre_token, t_token **token);
void		option_finder(char *str, t_token **token);
void		arg_finder(char *str, t_token **token);
int			tablen(char **tab);
int			reallocate_tab(char ***tab, char *str);
void		free_struct(t_token **token);
#endif
