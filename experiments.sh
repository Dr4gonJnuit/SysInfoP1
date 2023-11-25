#!/bin/bash

INGINIOUS="true"

LAUNCH_FILE=philo
make times LAUNCH=$LAUNCH_FILE
cat "performance/csv/temps_$LAUNCH_FILE.csv"
