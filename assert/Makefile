CC:=gcc
CFLAGS:=

ASSERT_OBJ=assert.o main.o

.DEFAULT:all

all: assert

assert: $(ASSERT_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:clean

clean:
	@rm -rf assert
	@rm -rf *.o
	@rm -rf a.out
