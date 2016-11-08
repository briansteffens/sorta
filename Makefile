default: build

setup:
	mkdir -p bin

build: setup
	gcc -o bin/run src/main.c src/sorta.c

test: setup
	gcc -o bin/test test/test.c src/sorta.c

clean:
	rm -rf bin
