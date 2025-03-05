build:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -lm -o game

run:
	./game

clean:
	rm game