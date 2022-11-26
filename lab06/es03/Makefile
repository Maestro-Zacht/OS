.PHONY: run

run: main
	./main 3 inp out 5

main: main.c
	gcc -g -Wall -o $@ $^ -lpthread
