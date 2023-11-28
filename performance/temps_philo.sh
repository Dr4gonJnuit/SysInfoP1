#!/bin/bash

if [ -z "$(find "performance")" ]; then # if we are already in the performance folder
    echo "n,m_p1,m_p2,m_p3,m_p4,m_p5" > "csv/temps_philo.csv"
    cd ..
else # if we call the script with make times
    echo "n,m_p1,m_p2,m_p3,m_p4,m_p5" > "performance/csv/temps_philo.csv"
fi

make -s

for i in 2 4 8 16 32 64; do
    echo -n "$i" >>"performance/csv/temps_philo.csv"

    for j in 1 2 3 4 5; do
        time_start=$(date +%s.%N)                      # time in nanoseconds (start)
        ./main -f philo -n $i                          # launch the program
        time_end=$(date +%s.%N)                        # time in nanoseconds (end)
        runtime=$(echo "$time_end - $time_start" | bc) # execution time for philo
        echo -n ",$runtime" >>"performance/csv/temps_philo.csv" # Insert $runtime next to the existing code
    done

    echo "" >>"performance/csv/temps_philo.csv" # Insert a new line
done

rm -f main
cd performance
