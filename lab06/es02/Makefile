.PHONY: run

run: main
	./main 3 inp out

main: main.c
	gcc -g -Wall -o $@ $^ -lpthread
