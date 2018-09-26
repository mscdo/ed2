all:
	gcc -std=c99 -Wall -g -c main.c functions.c functions.h
	gcc -Wall -g -o -lm  main main.o functions.o

clean:
	rm -rf *.o	