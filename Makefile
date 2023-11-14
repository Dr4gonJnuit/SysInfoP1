CC = gcc
FILES = src

philo :
	$(CC) -o philo $(FILES)/philosophes.c main.c

reader_writer :
	$(CC) -o reader_writer $(FILES)/reader_writer.c main.c

run :
	make -s $(1)
	./$(1)

clean :
	rm -f philo
	rm -f reader_writer
	clear
