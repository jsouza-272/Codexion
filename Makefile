all:
	cc -Wall -Wextra -Werror -pthread *.c -o codexion

clean:
	@rm codexion

norm:
	norminette