prog := dgemv
prog_objs := dgemv.o hpctimer.o

CC := gcc
CFLAGS := -fopenmp -o -Wall -g
LDFLAGS := -lm

.PHONY: all clean

all: $(prog)

$(prog): $(prog_objs)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

dgemm.o: dgemv.c
hpctimer.o: hpctimer.c hpctimer.h

clean:
	@rm -rf *.o $(prog)
