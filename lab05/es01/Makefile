.PHONY: run

run: main
	./main

main: main.o
	gcc -g -Wall -o $@ $^

main.o: main.c
	gcc -c $<
