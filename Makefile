default: build

setup:
	mkdir -p bin

build: setup
	gcc -Wall -o bin/run src/main.c src/sorta.c src/heap.c src/hashing.c

test: setup
	gcc -Wall -o bin/test test/test.c src/sorta.c src/heap.c src/hashing.c -lbcunit

clean:
	rm -rf bin
