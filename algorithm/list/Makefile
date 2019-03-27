CC:=gcc
CFLAGS:=

LIST_OBJ=main.o

LIST_TARGET=list

.DEFAULT:all

all: $(LIST_TARGET)

$(LIST_TARGET): $(LIST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	@rm -rf *.o
	@rm -rf *.out
	@rm -rf $(LIST_TARGET)
