#!/bin/bash

LAUNCH_FILE=pc
make times LAUNCH=$LAUNCH_FILE
cat "performance/csv/temps_$LAUNCH_FILE.csv"
