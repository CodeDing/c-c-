CC:=gcc
CFLAGS:=

OBJ=heap.o

EXEC_TARGET=heap

.DEFAULT:all

all: $(EXEC_TARGET)

$(EXEC_TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)



.PHONY: clean
clean:
	@rm -rf *.o
	@rm -rf $(EXEC_TARGET)
