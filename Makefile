all:
	cc -Wall -Wextra -Werror -pthread -I ./includes src/*.c src/*/*.c -o codexion

clean:
	@rm codexion

norm:
	norminette