CC:=gcc
CFLAGS:=

.DEFAULT: all

all: hash

OBJ:=hash.o

hash:$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf a.out
	rm -rf *.o
	rm -rf hash
