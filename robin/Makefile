CC := g++

CFLAGS :=

all: robin

robin: robin.cpp
	$(CC) -o $@ $< $(CFLAGS)

.PHONY:
clean:
	rm -rf robin
	rm -rf *.o
