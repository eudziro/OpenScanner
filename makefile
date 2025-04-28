
all: link

link: main.o scanner.o validate_input.o print_help.o err_wrapper.o wrapper.o
	gcc -o wseek ./obj/*

main.o: main.c
	gcc -c main.c -o ./obj/main.o

validate_input.o: validate_input.c
	gcc -c validate_input.c -o ./obj/validate_input.o

print_help.o: print_help.c
	gcc -c print_help.c -o ./obj/print_help.o

scanner.o: scanner.c
	gcc -c scanner.c -o ./obj/scanner.o

wrapper.o: wrapper.c
	gcc -c wrapper.c -o ./obj/wrapper.o

err_wrapper.o: err_wrapper.c
	gcc -c err_wrapper.c -o ./obj/err_wrapper.o


