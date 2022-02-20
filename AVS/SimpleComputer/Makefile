flags = -Wall #-Werror

all: src


#src

src: build/src build/src/main.o build/src/mySimpleComputer.o build/src/myTerm.o build/src/myBigChars.o build/src/myReadkey.o 
	gcc $(flags) build/src/*.o  -o bin/mySimpleComputer 

build/src:
	mkdir -p build/src

build/src/main.o: src/main.c
	gcc $(flags) -c src/main.c -o build/src/main.o

build/src/mySimpleComputer.o: src/mySimpleComputer.c
	gcc $(flags) -c src/mySimpleComputer.c -o build/src/mySimpleComputer.o

build/src/myTerm.o: src/myTerm.c
	gcc $(flags) -c src/myTerm.c -o build/src/myTerm.o

build/src/myBigChars.o: src/myBigChars.c
	gcc $(flags) -c src/myBigChars.c -o build/src/myBigChars.o

build/src/myReadkey.o: src/myReadkey.c
	gcc $(flags) -c src/myReadkey.c -o build/src/myReadkey.o




.PHONY: clean all

clean:
	rm -rf build/src/* bin/* build/test/*
