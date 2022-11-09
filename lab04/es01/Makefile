.PHONY: run redirect

run: main
	./main

main: main.o
	gcc -g -Wall -o $@ $^

main.o: main.c
	gcc -c $<

redirect: main
	./main < inFile.txt > pariFile.txt 2> dispariFile.txt