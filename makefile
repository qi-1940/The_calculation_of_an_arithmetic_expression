stack.o:stack.h
	gcc -c stack.c
main:stack.o
	gcc -g  stack.o main.c -o main  