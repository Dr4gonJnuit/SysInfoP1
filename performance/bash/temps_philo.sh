NAME_FILE="performance/csv/temps_philo_POSIX.csv"
#NAME_FILE="performance/csv/temps_philo_TAS.csv"
#NAME_FILE="performance/csv/temps_philo_TTAS.csv"

echo "n,t_1,t_2,t_3,t_4,t_5" > $NAME_FILE

for i in 2 4 8 16 32 64; do
    echo -n "$i" >> $NAME_FILE

    for j in 1 2 3 4 5; do
        runtime=$(/usr/bin/time -f "%e" ./main -f philo -n $i 2>&1 >/dev/null)
        echo -n ",$runtime" >> $NAME_FILE
    done

    echo "" >> $NAME_FILE
done

if [ $1 = "cat" ]; then
    cat $NAME_FILE
fi
