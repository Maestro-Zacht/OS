.PHONY: run

run: main
	./main comandi.txt

main: main.o
	gcc -o $@ $^

main.o: main.c
	gcc -c $<