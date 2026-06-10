SCHEDULER= fifo

all:
	cc -Wall -Wextra -Werror -pthread -I ./includes src/*.c src/*/*.c -o codexion

clean:
	@rm codexion

norm:
	norminette

run: all
	clear
#	./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
	./codexion 			2				1000				100				100				100						20						400			 $(SCHEDULER)
	@rm codexion

debug: all
	clear
#	./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
	./codexion 			20				100000 				100 			100 			100 			 		1 						400 		 $(SCHEDULER) | grep COMPILE
	@rm codexion

val: all
	clear
#	./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
	valgrind --leak-check=full --show-leak-kinds=all ./codexion 				2				1000				100				100				100						1						100			 $(SCHEDULER)
	@rm codexion
