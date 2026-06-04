# Parser
### Via linha de commando
-    number_of_coders: int > 0
-    time_to_burnout: int > 0 (ms)
-    time_to_compile: int > 0 (ms)
-    time_to_debug: int > 0 (ms)
-    time_to_refactor: int > 0 (ms)
-    number_of_compiles_required: int > 0
-    dongle_cooldown: int > 0 (ms)
-    scheduler: FIFO | EDF

### Erros
-	fazer um enum de erros

# Coder e Dongles
- ## Mesa
	-	next table
	-	prev table
	-	coder e dongle
	-	cada mesa tem um coder e um dongle

- ###	Coder
	-	cada coder tem suas informacoes  
		```bash
		# last compile
		# thread
		# time_to_burnout: int > 0 (ms)
		# time_to_compile: int > 0 (ms)
		# time_to_debug: int > 0 (ms)
		# time_to_refactor: int > 0 (ms)
		```

- ### Dongle
	-	cada dongle tem suas informacoes
		```bash
		# last use
		# dongle_cooldown: int > 0 (ms)
		```
	-	implementar o cooldown

# Moder
-	implementar o burnout dos coders