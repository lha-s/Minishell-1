NAME		=	Minishell

HEAD 		=	./includes/*.h

INC			=	-I./includes/

C			=	gcc

FLAGS		=	-Wall -Wextra -Werror

INFO		=	echo "Minishell is compiling..." &&

LIBFT		=	./srcs/utils/libft/libft.a


SRCS		= ./srcs/utils/common_utils.c \
				./srcs/utils/free_utils.c \
				./srcs/utils/get_next.c \
				./srcs/utils/struct_utils.c \
				./srcs/utils/write_utils.c \
				./srcs/input_process.c \
				./srcs/minishell.c
OBJ			=	$(SRCS:.c=.o)

all: 	$(NAME)

$(OBJ): $(HEAD)

$(NAME): $(OBJ)
	@echo "\033[0;35mLibft is compiling" \
		&& sleep 1  && echo "...\033[0m"
	@cd ./srcs/libft && make
	@echo "\033[0;32mLibft compilation was succesfull.\033[0m"
	@cd ..
	@echo "\033[0;35mMinishell is compiling" \
		&& sleep 1  && echo "...\033[0m" \
		&& make process

process: $(OBJ)
	@$(CC) $(FLAGS) $(INC) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "\033[0;32mCub3D compilation was succesfull.\033[0m"

%.o: %.c
	@$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
	rm -f $(OBJ)
	@echo "\033[0;31mCub3D object files deletion complete\033[0m"

test:
	valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=no ./$(NAME)

fclean: clean
	@rm -f $(NAME)
	@cd ./srcs/utils/libft && make clean && cd ..
	@echo "\033[0;31mLibft objects files deletion complete\033[0m"

re:
	@make clean
	@make process

.PHONY: all clean fclean re
