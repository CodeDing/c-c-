CC:=gcc
CFLAGS:=

STACK_OBJ=main.o stack.o

.DEFAULT:all

all: stack

stack: $(STACK_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

#stack.o: stack.h stack.c
#	$(CC) -c -o $@ $< $(CLFAGS)


.PHONY: clean
clean:
	@rm -rf *.o
	@rm -rf main stack
