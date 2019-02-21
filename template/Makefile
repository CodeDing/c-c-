
CC := g++
CFLAGS := -std=c++11

all: template

template: template.cpp
	$(CC) -o $@ $< $(CFLAGS)

#template.o: template.cpp
#	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: 
clean:
	rm -rf template
	rm -rf *.o
