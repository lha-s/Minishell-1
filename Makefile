NAME		=	Minishell

HEAD 		=	./includes/*.h

INC			=	-I./includes/

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror

INFO		=	echo "Minishell is compiling..." &&

LIBFT_PATH	=	./srcs/utils/libft

LIBFT		=	$(LIBFT_PATH)/libft.a

SRCS		= ./srcs/utils/common_utils.c \
				./srcs/utils/common_utils2.c \
				./srcs/utils/free_utils.c \
				./srcs/utils/display.c \
				./srcs/utils/struct_utils.c \
				./srcs/utils/write_utils.c \
				./srcs/utils/variable_utils.c \
				./srcs/input_process.c \
				./srcs/minishell.c \
				./srcs/cmds.c \
				./srcs/execution.c \
				./srcs/piping.c \
				./srcs/built_in/pwd.c \
				./srcs/built_in/env.c \
				./srcs/built_in/export.c \
				./srcs/built_in/unset.c \
				./srcs/built_in/cd.c \
				./srcs/built_in/echo.c


OBJ			=	$(SRCS:.c=.o)

all: 	$(NAME)

$(OBJ): $(HEAD)

$(NAME): $(OBJ)
	@echo "\033[0;35mLibft is compiling" \
		&& sleep 1  && echo "...\033[0m"
	@cd ./srcs/utils/libft && make
	@echo "\033[0;32mLibft compilation was succesfull.\033[0m"
	@cd ..
	@echo "\033[0;35mMinishell is compiling" \
		&& sleep 1  && echo "...\033[0m" \
		&& make process

process: $(OBJ)
	@$(CC) $(FLAGS) $(INC) -lreadline -o $(NAME) $(OBJ) $(LIBFT)
	@make clean && echo "\033[0;32mMinishell compilation was succesfull.\033[0m"

%.o: %.c
	@$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
	make -C $(LIBFT_PATH) $@
	rm -f $(OBJ)
	@echo "\033[0;31mMinishell object files deletion complete\033[0m"

test:
	valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=no ./$(NAME)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@echo "\033[0;31mLibft objects files deletion complete\033[0m"

re:
	@make clean
	@make process

.PHONY: all clean fclean re
