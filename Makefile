default: build

setup:
	mkdir -p bin

build: setup
	gcc -o bin/run src/main.c src/shared.c src/insertion.c src/selection.c

test: setup
	gcc -o bin/test test/test.c src/shared.c src/insertion.c src/selection.c

clean:
	rm -rf bin
