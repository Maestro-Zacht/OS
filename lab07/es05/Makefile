.PHONY: run

run: main
	./main &
	sleep 1
	./script.sh main 1

main: main.c
	gcc -g -Wall -o $@ $^