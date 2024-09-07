make: kilo.c
	$(CC) kilo.c -o kilo.o -Wall -Wextra -pedantic -std=c99

clean: kilo.c
	rm -f *.o
