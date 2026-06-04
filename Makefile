all:
	cc -Wall -Wextra -Werror -pthread -I ./includes src/*.c src/*/*.c -o codexion

clean:
	@rm codexion

norm:
	norminette

run: all
	clear
	./codexion 2 1000 100 100 100 5 100 fifo
	@rm codexion

debug: all
	clear
	./codexion 2 1000 100 100 100 1 100 fifo | grep COMPILE
	@rm codexion