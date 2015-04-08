test:test.o
	gcc -o test test.o
test.o:test.c
	gcc -o test.o -c test.c
clean:
	rm test test.o


