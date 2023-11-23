echo "n,temps_philo,temps_reader_writer" >"temps_execution.csv"

cd ..
make

for i in 2 4 8 16 32 64; do
    time_start=$(date +%s.%N)                      # time in nanoseconds (start)
    ./main -f philo -n $i                          # launch the program
    time_end=$(date +%s.%N)                        # time in nanoseconds (end)
    runtime=$(echo "$time_end - $time_start" | bc) # execution time for philo

    time_start=$(date +%s.%N)                   # time in nanoseconds (start)
    ./main -f reader_writer -i $(($i/2)) -j $(($i/2)) # launch the program
    time_end=$(date +%s.%N)                     # time in nanoseconds (end)
    runtime2=$(echo "$time_end - $time_start" | bc) # execution time for reader_writer

    echo "$i,$runtime,$runtime2" >>"performance/temps_execution.csv"
done

rm -f main
cd performance
