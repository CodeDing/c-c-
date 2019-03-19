CC:=gcc

CFLAGS:=

OBJ:= max_swap.o

.DEFAULT: all

all: max_swap

max_swap: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf a.out
	rm -rf *.o
	rm -rf max_swap

