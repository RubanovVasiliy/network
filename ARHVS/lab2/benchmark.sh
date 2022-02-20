#!/bin/bash

# initial values
OUTFILE="results.csv"
OPTIMIZATION="O0"
TASK="sin"
OPERANDTYPE="int"
COUNT="10"

# inline command parser

while [[ $# -gt 0 ]]; do
  key="$1"

  case $key in
  -n | --num)
    COUNT="$2"
    shift # past argument
    shift # past value
    ;;
  -f | --file)
    OUTFILE="$2"
    shift # past argument
    shift # past value
    ;;
  -t | --task)
    TASK="$2"
    shift # past argument
    shift # past value
    ;;
  -p | --operandType)
    OPERANDTYPE="$2"
    shift # past argument
    shift # past value
    ;;
  -o | --optimization)
    OPTIMIZATION="$2"
    shift # past argument
    shift # past value
    ;;
  -h | --help)
    HELP="--help"
    shift # past argument
    ;;
  *) # unknown option
    ;;
  esac
done


# log inline parser values
echo "Usage example:"
echo "./benchmark.sh -n 10 -t log -p int -o O1"
echo

if test -f "$OUTFILE"; then
  echo
else
  printf "PModel,Task,OpType,Opt,InsCount,Timer,Time,LNum,AvTime,AbsError,RelError,TaskPerf\n" >>"${OUTFILE}"
fi

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
  lscpu | grep -e "Model name:" -e "Имя модели:" | awk '{for (i=3; i<=NF; i++) printf "%s",$i} END{printf ","}' >>"${OUTFILE}"
elif [[ "$OSTYPE" == "darwin"* ]]; then
  sysctl -n machdep.cpu.brand_string | awk '{printf "%s",$0}' >>"${OUTFILE}"
else
  echo "Unknown OS"
fi


printf "$COUNT$TASK," >>"${OUTFILE}"
printf "$OPERANDTYPE," >>"${OUTFILE}"
printf "$OPTIMIZATION," >>"${OUTFILE}"

CLEARCOUNT="$COUNT"
if [ -n "$COUNT" ]; then
  COUNT="-n ${COUNT}"
fi

if [ -n "$TASK" ]; then
  TASK="-t ${TASK}"
fi

if [ -n "$OPERANDTYPE" ]; then
  OPERANDTYPE="-p ${OPERANDTYPE}"
fi


echo "COUNT        = ${COUNT}"
echo "OUTFILE      = ${OUTFILE}"
echo "TASK         = ${TASK}"
echo "OPERANDTYPE  = ${OPERANDTYPE}"
echo "OPTIMIZATION = ${OPTIMIZATION}"
echo "DEFAULT      = ${DEFAULT}"

echo "g++ -std=c++17 -Wall -Werror -${OPTIMIZATION} main.cpp -o main"
g++ -std=c++17 -Wall -"$OPTIMIZATION" main.cpp -o main

echo "./main ${COUNT} ${TASK} ${OPERANDTYPE}"
EXEC="./main $COUNT $OPERANDTYPE $TASK"
$EXEC


TIME=$(cat time.txt | awk '{print $1}')
SINGLETIME=$(cat time.txt | awk '{print $2}')

ABSERROR=$(bc <<< "scale=6; $CLEARCOUNT/(3600*1000*100000)-$TIME/$CLEARCOUNT+1")
RELERROR=$(bc <<< "scale=6; $ABSERROR/$TIME/$CLEARCOUNT")
#echo "================================${ABSERROR}"
#echo "================================${RELERROR}"
AVTIME=$(bc <<< "scale=6; $TIME/$CLEARCOUNT")
LNUM=$(cat results.csv | wc -l)

valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./main 
INSCOUNT=$(cat callgrind.out | grep summary | awk '{print $2}')
TASKPERF=$(bc <<< "scale=2; $INSCOUNT/$TIME")


printf "$INSCOUNT," >>"${OUTFILE}"
printf "clock_gettime," >>"${OUTFILE}"
printf "$TIME," >>"${OUTFILE}"
printf "$LNUM," >>"${OUTFILE}"
printf "$AVTIME," >>"${OUTFILE}"
printf "$ABSERROR," >>"${OUTFILE}"
printf "$RELERROR," >>"${OUTFILE}"
printf "$TASKPERF" >>"${OUTFILE}"

printf "\n" >>"${OUTFILE}"