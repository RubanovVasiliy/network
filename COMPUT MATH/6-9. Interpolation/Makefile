flags = -Wall -Werror

all: src


src: main.c
	gcc $(flags) main.c -o prog -lm

.PHONY: clean all

clean:
	rm -rf prog
