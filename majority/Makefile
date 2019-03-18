CC:=gcc
CFLAGS:=

OBJ:=majority.o

.DEFAULT: all

all: majority

majority:$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

clean:
	rm -rf a.out
	rm -rf *.o
	rm -rf majority
