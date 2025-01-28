test: test.o scanner.o
	gcc -o test test.o scanner.o

test2: test.o scannerRev.o
	gcc -o test2 test.o scannerRev.o

scannerRev.o: scannerRev.c
	gcc -c scannerRev.c

test.o: test.c
	gcc -c test.c

scanner.o: scanner.c
	gcc -c scanner.c
