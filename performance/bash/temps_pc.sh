#!/bin/bash

if [ -z "$(find "performance")" ]; then # if we are already in the performance folder
    echo "n,m_pc1,m_pc2,m_pc3,m_pc4,m_pc5" >"csv/temps_pc.csv"
    cd ..
else # if we call the script with make times
    echo "n,m_pc1,m_pc2,m_pc3,m_pc4,m_pc5" >"performance/csv/temps_pc.csv"
fi

make -s perso

for i in 2 4 8 16 32 64; do
    echo -n "$i" >>"performance/csv/temps_pc.csv"

    for j in 1 2 3 4 5; do
        time_start=$(date +%s.%N)                             # time in nanoseconds (start)
        ./main -f produc_conso -i $(($i / 2)) -j $(($i / 2)) # launch the program
        time_end=$(date +%s.%N)                               # time in nanoseconds (end)
        runtime=$(echo "$time_end - $time_start" | bc)       # execution time for reader_writer
        echo -n ",$runtime" >>"performance/csv/temps_pc.csv" # Insert $runtime next to the existing code
    done

    echo "" >>"performance/csv/temps_pc.csv" # Insert a new line
done

make clean
cd performance
