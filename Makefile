CC = gcc
FLAGS = -Wall -Werror
HEADER_DIRECTORY = -Iheaders # Look in headers folder for the *.h /!\ it's normal if the name is connected to I, it's a convention /!\.
LIBS = -lpthread

run : main.c src/philosophes.c src/reader_writer.c src/includes.c
	$(CC) $(HEADER_DIRECTORY) $(FLAGS) -o main $^ $(LIBS)

%o : %.c
	$(CC) $(HEADER_DIRECTORY) $(FLAGS) -c $< -o $@

clean :
	rm -f main
	# ...
	clear

.PHONY: clean
