CC = gcc
FLAGS = -Wall -Werror
HEADER_DIRECTORY = -Iheaders # Look in headers folder for the *.h /!\ it's normal if the name is connected to I, it's a convention /!\.
LIBS = -lpthread

philo : main.c src/philosophes.c src/includes.c
	$(CC) $(HEADER_DIRECTORY) $(FLAGS) -o philo $^ $(LIBS)

run_philo : philo # Ensure that philo exist. Otherwise, launch make philo.
	./philo -n $(filter-out $@,$(MAKECMDGOALS))

run : main.c src/philosophes.c src/includes.c
	$(CC) $(HEADER_DIRECTORY) $(FLAGS) -o main $^ $(LIBS)

clean :
	rm -f philo
	rm -f main
	rm -f todel
	rm -f todel.*

.PHONY: clean