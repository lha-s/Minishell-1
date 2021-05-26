NAME                    = minishell
HEADER                  = ./includes/minishell.h
LIBFT                   = libft.a
LIBFT_PATH              = $(SRCS_PATH)/utils/libft
SRCS_PATH				= ./srcs
BUILT_IN				= built_in
UTILS					= utils
SRCS_NAME               = 	minishell.c \
							input_process.c \
							$(UTILS)/common_utils.c \
							$(UTILS)/free_utils.c \
							$(UTILS)/get_next.c \
							$(UTILS)/struct_utils.c \
							$(UTILS)/write_utils.c \
							$(BUILT_IN)/bash_builtin.c \
							$(BUILT_IN)/pwd_builtin.c \
							

SRCS			= $(addprefix $(SRCS_PATH)/,$(SRCS_NAME))
OBJS            = $(SRCS:.c=.o)
CC              = gcc
RM              = rm -f
CFLAGS          = #-Wall -Wextra -Werror

all     : $(LIBFT) $(NAME)

$(NAME) : $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) -o $@ *.o $(LIBFT)

%.o : %.c $(HEADER) $(LIBFT)
	$(CC) $(CFLAGS) -I $(HEADER) -c $< 

clean   :
	make -C $(LIBFT_PATH) $@
	$(RM) $(OBJS)
	rm ./*.o

fclean  : clean
	$(RM) ./libft.a
	$(RM) ./srcs/utils/libft/libft.a
	$(RM) $(NAME)

re:     fclean all

$(LIBFT):
	make -C $(LIBFT_PATH) all
	cp ./srcs/utils/libft/libft.a libft.a

.PHONY: all fclean clean re