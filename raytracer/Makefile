CC=g++

CFLAGS=-Wall
LDFLAGS=-lpng

all: main.cpp canvas.o raytracer.o
	$(CC) main.cpp canvas.o raytracer.o $(CFLAGS) -o render $(LDFLAGS)
	./render
	feh output.png

canvas.o: canvas.cpp canvas.hpp
	$(CC) -c canvas.cpp $(CFLAGS)

raytracer.o: raytracer.cpp raytracer.hpp canvas.hpp
	$(CC) -c raytracer.cpp $(CFLAGS)

clean:
	rm -f render
	rm -f canvas.o
	rm -f raytracer.o
	rm -f output.png
