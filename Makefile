CC = gcc
FLAGS = -Wall -Werror
HEADER_DIRECTORY = -Iheaders # Look in headers folder for the *.h /!\ it's normal if the name is connected to I, it's a convention /!\.
LIBS = -lpthread

philo : main.c src/philosophes.c src/includes.c
	$(CC) $(HEADER_DIRECTORY) $(FLAGS) -o philo $^ $(LIBS)

run_philo : philo # Ensure that philo exist. Otherwise, launch make philo.
	./philo -n $(filter-out $@,$(MAKECMDGOALS))

reader_writer : main.c src/reader_writer.c src/includes.c
	$(CC) $(HEADER_DIRECTORY) $(FLAGS) -o reader_writer $^ $(LIBS)

run_reader_writer : reader_writer # Ensure that reader_writer exist. Otherwise, launch make reader_writer.
	./reader_writer -r $(filter-out $@,$(MAKECMDGOALS)) -w $(filter-out $@,$(MAKECMDGOALS))

run : main.c src/philosophes.c src/reader_writer.c src/includes.c
	$(CC) $(HEADER_DIRECTORY) $(FLAGS) -o main $^ $(LIBS)

clean :
	rm -f philo
	rm -f reader_writer
	rm -f main
	rm -f todel
	rm -f todel.*

.PHONY: clean