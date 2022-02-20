#!/bin/bash

# initial values


#./main -m RAM -l 3 -s 54525952

THREADS="8"
SIZE=5000

for (( THREADS=2; THREADS<=8; THREADS+=2 ))
do
 EXEC="./main -s $SIZE -t $THREADS"
 $EXEC
done


SIZE=10000

for (( THREADS=2; THREADS<=8; THREADS+=2 ))
do
 EXEC="./main -s $SIZE -t $THREADS"
 $EXEC
done

