default: build

setup:
	mkdir -p bin

build: setup
	gcc -o bin/run src/main.c src/sorto.c

test: setup
	gcc -o bin/test test/test.c src/sorto.c

clean:
	rm -rf bin
