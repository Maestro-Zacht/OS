.PHONY: run

run: main
	./main 3

main: main.o
	gcc -Wall -o $@ $^

main.o: main.c
	gcc -g -c $<
