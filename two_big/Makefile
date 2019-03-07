CC=gcc
CFLAGS=

OBJ=main.o
TARGET=two_big_multiply_calc
.DEFAULT: all

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf a.out *.o
	rm -rf $(TARGET)

