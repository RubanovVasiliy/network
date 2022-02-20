#!/bin/bash

# initial values


MODE="flash"
SIZE="1048576"
COUNT="1"

#./main -m RAM -l 3 -s 54525952

for (( SIZE=4194304; SIZE<=83886081; SIZE+=4194304 ))
do
 echo "./main -m ${MODE} -l ${COUNT} -s ${SIZE}"
 EXEC="./main -m $MODE -l $COUNT -s $SIZE"
 $EXEC
done


