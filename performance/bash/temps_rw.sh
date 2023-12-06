#!/bin/bash

if [ -z "$(find "performance")" ]; then # if we are already in the performance folder
    echo "n,m_rw1,m_rw2,m_rw3,m_rw4,m_rw5" >"csv/temps_rw.csv"
    cd ..
else # if we call the script with make times
    echo "n,m_rw1,m_rw2,m_rw3,m_rw4,m_rw5" >"performance/csv/temps_rw.csv"
fi

make -s

for i in 2 4 8 16 32 64; do
    echo -n "$i" >>"performance/csv/temps_rw.csv"

    for j in 1 2 3 4 5; do
        time_start=$(date +%s.%N)                             # time in nanoseconds (start)
        ./main -f reader_writer -i $(($i / 2)) -j $(($i / 2)) # launch the program
        time_end=$(date +%s.%N)                               # time in nanoseconds (end)
        runtime=$(echo "$time_end - $time_start" | bc)       # execution time for reader_writer
        echo -n ",$runtime" >>"performance/csv/temps_rw.csv" # Insert $runtime next to the existing code
    done

    echo "" >>"performance/csv/temps_rw.csv" # Insert a new line
done

rm -f main
cd performance
