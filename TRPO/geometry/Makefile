FLAGS = -Wall -Werror


all: bin build bin/g bin/t

#src

bin/g: build/src/main.o build/src/func.o
	gcc $(FLAGS) build/src/main.o build/src/func.o -o bin/g -lm

build/src/main.o: src/main.c
	gcc $(FLAGS) -c src/main.c -o build/src/main.o

build/src/func.o: src/func.c
	gcc $(FLAGS) -c src/func.c -o build/src/func.o

#test

bin/t: build/test/main.o build/test/func.o build/src/func.o
	gcc $(FLAGS) build/test/main.o build/test/func.o build/src/func.o -o bin/t -lm

build/test/main.o: test/main.c
	gcc $(FLAGS) -c test/main.c -o build/test/main.o

build/test/func.o: test/func.c
	gcc $(FLAGS) -c test/func.c -o build/test/func.o

bin:
	mkdir -p bin
	mkdir -p bin

build:
	mkdir -p build/test
	mkdir -p build/src

run: all
	./bin/g
	./bin/t

.PHONY: clean all run

clean:
	rm -rf build bin