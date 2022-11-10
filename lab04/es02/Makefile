.PHONY: run

run: main
	./main input.txt

main: main.o
	gcc -g -Wall -o $@ $^

main.o: main.c
	gcc -c $<
