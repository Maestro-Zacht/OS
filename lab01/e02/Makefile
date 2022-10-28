.PHONY: install clean distclean
COMPILER=gcc

main: main.o
	$(COMPILER) -o $@ $^

main.o: main.c
	$(COMPILER) -c $<

install: main
	mkdir ../bin
	mv -t ../bin ./main

clean:
	rm -f main

distclean: clean
	rm -rf ../bin

run: main
	./$< lab01e01in.txt test.txt