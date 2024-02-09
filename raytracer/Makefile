CC=g++

CFLAGS=-Wall
LDFLAGS=-lpng

all: main.cpp canvas.o
	$(CC) main.cpp canvas.o $(CFLAGS) -o render $(LDFLAGS)
	./render
	feh output.png

canvas.o: canvas.cpp canvas.hpp
	$(CC) -c canvas.cpp $(CFLAGS)

clean:
	rm -f render
	rm -f canvas.o
	rm -f output.png
