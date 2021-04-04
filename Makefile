CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -g
DEPS = code_breaker.h stdio.h stdlib.h  time.h
OBJS = code_breaker.o game.o

%.o: %.c $DEPS
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: all

all: play code_breaker.o game.o

play: $(OBJS)
	$(CC) $(OBJS) -o play

code_breaker.o: code_breaker.c
	$(CC) -c code_breaker.c -o code_breaker.o

game.o: game.c code_breaker.o
	$(CC) $(CFLAGS) -c game.c -o game.o



clean:
	rm *.o
