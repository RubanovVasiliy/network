#!/bin/bash

# initial values


#./main -m RAM -l 3 -s 54525952

BLOCK_SIZE="8"

EXEC="./main -s 10000 -b $BLOCK_SIZE"
$EXEC

BLOCK_SIZE="8"
for (( SIZE=1000; SIZE<=10000; SIZE+=1000 ))
do
 EXEC="./main -s $SIZE -b $BLOCK_SIZE"
 $EXEC
done


SIZE="1000"
for (( BLOCK_SIZE=1; BLOCK_SIZE<=1024; BLOCK_SIZE*=2 ))
do
 EXEC="./main -s $SIZE -b $BLOCK_SIZE"
 $EXEC
done

for (( SIZE=1000; SIZE<=10000; SIZE+=1000 ))
do
 EXEC="./main -s $SIZE"
 $EXEC
done



