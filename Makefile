FLAGS= -Wall -Wextra -Werror -pthread -I ./includes
CC= cc

NAME= codexion

SRC= src/errors/errors.c src/init/init.c src/init/init2.c src/parser/parser.c \
	src/threads/check_burnout.c src/threads/coder_routine.c src/threads/edf.c \
	src/threads/fifo.c src/threads/moder_routine.c src/utils/free_all.c \
	src/utils/in.c src/utils/time.c src/utils/utils.c src/codexion.c

OBJ= $(addprefix obj/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f codexion

fclean: clean
	@rm -rf obj

re: fclean all

.PHONY: all bonus clean fclean re