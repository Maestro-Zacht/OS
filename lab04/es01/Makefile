.PHONY: run redirect stringhe

run: main
	./main

main: main.o
	gcc -g -Wall -o $@ $^

main.o: main.c
	gcc -c $<

redirect: main
	./main < inFile.txt > pariFile.txt 2> dispariFile.txt

stringhe:
	cat ./es01b/lab01.txt ./es01b/lab02.txt ./es01b/lab03.txt | wc -w