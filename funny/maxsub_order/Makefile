CC:=gcc
CXX:=g++
CFLAGS:= 

all: search_max_sub_order search_max_sub_matrix

search_max_sub_order: search_max_sub_order.c
	$(CC) -o $@ $< $(CFLAGS)
search_max_sub_matrix: search_max_sub_matrix.cpp
	$(CXX) -o $@ $< $(CFLAGS)


.PHONY:
clean:
	@rm -rf *.o
	@rm -rf *.out
	@rm -rf search_max_sub_order search_max_sub_matrix
