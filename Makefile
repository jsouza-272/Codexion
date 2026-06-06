all:
	cc -Wall -Wextra -Werror -pthread -I ./includes src/*.c src/*/*.c -o codexion

clean:
	@rm codexion

norm:
	norminette

run: all
	clear
	./codexion 5 1000 100 100 100 1 100 edf
	@rm codexion

debug: all
	clear
	./codexion 5 1000 100 100 100 1 100 fifo | grep COMPILE
	@rm codexion