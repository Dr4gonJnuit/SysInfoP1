CC = gcc
FILES = writer-reader

main :
	$(CC) -o main $(FILES)/reader.c $(FILES)/writer.c main.c

run :
	make -s main
	./main

clean :
	rm -f main
	clear