#NAME_FILE="performance/csv/temps_prod_cons_POSIX.csv"
#NAME_FILE="performance/csv/temps_prod_cons_TAS.csv"
NAME_FILE="performance/csv/temps_prod_cons_TATAS.csv"

echo "n,t_1,t_2,t_3,t_4,t_5" > $NAME_FILE

for i in 2 4 8 16 32 64; do
    echo -n "$i" >> $NAME_FILE

    for j in 1 2 3 4 5; do
        runtime=$(/usr/bin/time -f "%E" ./main -f prod_cons -n $(($i / 2)) 2>&1 >/dev/null)
        # Convert the time to seconds
        minutes=$(echo $runtime | cut -d: -f1)
        seconds=$(echo $runtime | cut -d: -f2 | cut -d. -f1)
        milliseconds=$(echo $runtime | cut -d: -f2 | cut -d. -f2)
        total_seconds=$(echo "scale=3; $minutes*60 + $seconds + $milliseconds/1000" | bc)
        echo -n ",$total_seconds" >> $NAME_FILE
    done

    echo "" >> $NAME_FILE
done

if [ $1 = "cat" ]; then
    cat $NAME_FILE
fi
