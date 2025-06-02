CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: passgen

passgen: passgen.c
	$(CC) $(CFLAGS) -o passgen passgen.c

clean:
	rm -f passgen
