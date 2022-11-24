.PHONY: run

run: main
	./main 3

main: main.o
	gcc -g -Wall -o $@ $^

main.o: main.c
	gcc -c $<
