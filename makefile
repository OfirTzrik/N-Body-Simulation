default:
	gcc src/main.c src/funcs.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra -pedantic -o build/main
