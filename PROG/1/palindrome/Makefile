FLAGS = -Wall -Werror -pedantic

all: bin build bin/p

bin/p: build/src/main.o build/src/func.o build/src/strings.o
	gcc $(flags) build/src/main.o build/src/func.o build/src/strings.o -o bin/p

build/src/main.o: src/main.c
	gcc $(flags) -c src/main.c -o build/src/main.o

build/src/func.o: src/func.c
	gcc $(flags) -c src/func.c -o build/src/func.o

build/src/strings.o: src/strings.c
	gcc $(flags) -c src/strings.c -o build/src/strings.o

bin:
	mkdir -p bin

build:
	mkdir -p build/src

run: all
	./bin/p source/text.txt $(v)

.PHONY: clean

clean:
	rm -rf build bin