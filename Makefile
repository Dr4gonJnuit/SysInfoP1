CC = gcc
FLAGS = -Wall -Werror
HEADER_DIRECTORY = -Iheaders # Look in headers folder for the *.h /!\ it's normal if the name is connected to I, it's a convention /!\.
LIBS = -lpthread

philo : main.c src/philosophes.c #src/includes.c
	$(CC) $(HEADER_DIRECTORY) $(FLAGS) -o philo $^ $(LIBS)

run_philo : philo # Ensure that philo exist. Otherwise, launch make philo.
	./philo $(filter-out $@,$(MAKECMDGOALS))

clean :
	rm -f philo
	rm -f todel
	rm -f todel.*

.PHONY: clean