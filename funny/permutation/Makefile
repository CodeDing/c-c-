CC:=gcc
CXX:=g++
CFLAGS:=

OBJ=permutation.o

.DEFAULT: all

all: permutation

permutation: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)

.PHONY:clean

clean:
	@rm -f *.o
	@rm -f permutation
