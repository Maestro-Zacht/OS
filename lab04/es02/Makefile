.PHONY: run creainput

run: main
	./main input

main: main.o
	gcc -g -Wall -o $@ $^

main.o: main.c
	gcc -c $<

creafile: creafile.c
	gcc -g -Wall -o $@ $^

creainput: creafile
	./$<