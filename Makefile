all: build

build:
	gcc -o run src/main.c src/insertion.c

clean:
	rm run
