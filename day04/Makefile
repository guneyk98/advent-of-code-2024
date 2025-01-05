CC = gcc
CFLAGS = -std=c23 -O2 -Wall -Wextra -Werror -Wpedantic

all: 4a 4b

4a: 4a.c
	$(CC) 4a.c $(CFLAGS) -o $@

4b: 4b.c
	$(CC) 4b.c $(CFLAGS) -o $@

clean:
	rm -f 4a 4b