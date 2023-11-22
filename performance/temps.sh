cd ..
make run
echo "Resultat du temps d'execution" > "performance/temps_execution.txt"
for i in 2, 4, 8, 16, 32, 64
do
    echo "Nombre de threads : $i" >> "performance/temps_execution.txt"
    time_start=`date +%s.%N`
    ./main -f philo -n $i
    time_end=`date +%s.%N`
    runtime=$(echo "$time_end - $time_start" | bc)
    echo $runtime >> "performance/temps_execution.txt"
done
rm -f main
echo "Fin du test de performance" >> "performance/temps_execution.txt"
cd performance
