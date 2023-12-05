CC = gcc
FLAGS = -Wall -Werror
HEADER_DIRECTORY = -Iheaders # Look in headers folder for the *.h /!\ it's normal if the name is connected to I, it's a convention /!\.
LIBS = -lpthread
LAUNCH=NULL
ALL=0

run : main.c src/philosophes.c src/reader_writer.c src/produc_conso.c src/my_mutex.c src/includes.c
	$(CC) $(HEADER_DIRECTORY) $(FLAGS) -o main $^ $(LIBS)

times : performance/temps_philo.sh performance/temps_rw.sh performance/temps_pc.sh
	@if [ "$(LAUNCH)" = NULL ]; then\
		./performance/temps_philo.sh;\
		./performance/temps_rw.sh;\
		./performance/temps_pc.sh;\
	elif [ "$(LAUNCH)" = "philo" ]; then\
		./performance/temps_philo.sh;\
	elif [ "$(LAUNCH)" = "rw" ]; then\
		./performance/temps_rw.sh;\
	elif [ "$(LAUNCH)" = "pc" ]; then\
		./performance/temps_pc.sh;\
	else\
		echo "Error : wrong argument";\
	fi

TAS : performance/perf_TAS.c src/my_mutex.c src/includes.c
	$(CC) $(HEADER_DIRECTORY) $(FLAGS) -o perf_TAS $^ $(LIBS)

%o : %.c
	$(CC) $(HEADER_DIRECTORY) $(FLAGS) -c $< -o $@

clean :
	rm -f main
	rm -f perf_TAS
	@if [ $(ALL) -eq 1 ]; then\
		rm -f performance/csv/temps_*.csv;\
	fi
	# ...
	clear

.PHONY: clean
