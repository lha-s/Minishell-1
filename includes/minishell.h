/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alganoun <alganoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 08:54:52 by alganoun          #+#    #+#             */
/*   Updated: 2021/05/28 15:09:21 by alganoun         ###   ########lyon.fr   */
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
	struct s_cmd	*next;
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
void		cmd_parser(t_cmd **cmd);
int			init_struct(t_cmd **cmd);
int			execute_command(t_cmd **cmd);
void		free_tab(char ***tab, int count);
void		safe_free(char **str);
t_prcess	*ft_prcessnew(char *content);
void		ft_prcessadd_back(t_prcess **aprcess, t_prcess *new);
t_prcess	*ft_prcesslast(t_prcess *prcess);

#endif
