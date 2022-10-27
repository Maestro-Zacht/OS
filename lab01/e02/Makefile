.PHONY: compila

compila:
	gcc -o main main.c

install: compila
	mkdir ../bin
	mv -t ../bin ./main

clean:
	rm -f main

distclean: clean
	rm -rf ../bin