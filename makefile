test: test.o scanner.o
	gcc -o test test.o scanner.o

test.o: test.c
	gcc -c test.c

scanner.o: scanner.c
	gcc -c scanner.c

