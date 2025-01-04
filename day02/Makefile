CC = gcc
CFLAGS = -std=c23 -O2 -Wall -Wextra -Werror -Wpedantic

all: 2a 2b

2a: 2a.c
	$(CC) 2a.c $(CFLAGS) -o $@

2b: 2b.c
	$(CC) 2b.c $(CFLAGS) -o $@

clean:
	rm -f 2a 2b
