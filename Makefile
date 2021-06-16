SDL=$(shell sdl-config --cflags --libs)

default: main run

run: main
	./main

main: main.c
	gcc -std=c99 -Wall -Werror $(SDL) main.c -Og -g -o main -lSDL_ttf

web: main.html

main.html:
	emcc -O3 -s ASYNCIFY main.c -o main.html

clean:
	rm -f main main.js main.wasm main.html

.PHONY: default run web clean
