CC = gcc
CFLAGS = -std=c23 -O2 -Wall -Wextra -Werror -Wpedantic

all: 3a 3b

3a: 3a.c
	$(CC) 3a.c $(CFLAGS) -o $@

3b: 3b.c
	$(CC) 3b.c $(CFLAGS) -o $@

clean:
	rm -f 3a 3b
