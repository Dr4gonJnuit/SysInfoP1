CC = gcc
FLAGS = -Wall -Werror
HEADER_DIRECTORY = -Iheaders # Look in headers folder for the *.h /!\ it's normal if the name is connected to I, it's a convention /!\.
ALGO_DIR = src/algorithmes
MUT_DIR = src/attente_active
SH_DIR = performance/bash
LIBS = -lpthread

#############################
# Variables for the options #
#############################
LAUNCH=NULL
ALL=0

############
# Commands #
############
run : main TAS

main : main.c $(ALGO_DIR)/philosophes.c $(ALGO_DIR)/reader_writer.c $(ALGO_DIR)/produc_conso.c $(MUT_DIR)/my_semaphore.c $(MUT_DIR)/my_mutex.c src/includes.c
	$(CC) $(HEADER_DIRECTORY) $(FLAGS) -o main $^ $(LIBS)

TAS : performance/perf_TAS.c $(MUT_DIR)/my_mutex.c src/includes.c
	$(CC) $(HEADER_DIRECTORY) $(FLAGS) -o perf_TAS $^ $(LIBS)

#run : performance/perf_TAS.c $(MUT_DIR)/my_mutex.c src/includes.c
#	$(CC) $(HEADER_DIRECTORY) $(FLAGS) -o perf_TAS $^ $(LIBS)

tests : $(SH_DIR)/temps_philo.sh $(SH_DIR)/temps_rw.sh $(SH_DIR)/temps_pc.sh $(SH_DIR)/temps_TAS.sh
	@if [ "$(LAUNCH)" = NULL ]; then\
		./$(SH_DIR)/temps_philo.sh;\
		./$(SH_DIR)/temps_rw.sh;\
		./$(SH_DIR)/temps_pc.sh;\
	elif [ "$(LAUNCH)" = "philo" ]; then\
		./$(SH_DIR)/temps_philo.sh;\
	elif [ "$(LAUNCH)" = "rw" ]; then\
		./$(SH_DIR)/temps_rw.sh;\
	elif [ "$(LAUNCH)" = "pc" ]; then\
		./$(SH_DIR)/temps_pc.sh;\
	elif [ "$(LAUNCH)" = "tas" ]; then\
		./$(SH_DIR)/temps_TAS.sh;\
	else\
		echo "Error : wrong argument";\
	fi

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
