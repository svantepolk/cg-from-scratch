CC=g++

CFLAGS=-Wall
LDFLAGS=-lpng

all: main.cpp
	$(CC) main.cpp $(CFLAGS) -o render $(LDFLAGS)
	./render
	feh output.png
clean:
	rm -f render
	rm -f output.png
