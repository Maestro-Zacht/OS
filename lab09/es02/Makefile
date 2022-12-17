.PHONY: run


run: input main
	./main $<

input: input.txt prepare_file
	./prepare_file $< $@

prepare_file: prepare_file.c
	gcc -g -Wall -o $@ $^

main: main.c
	gcc -g -Wall -o $@ $^