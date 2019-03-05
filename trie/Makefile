CXX := g++
CXXFLAGS := -std=c++11

CC := gcc
CFLAGS :=

all: trie trie_ascii

trie: trie.cpp 
	$(CXX) -o $@ $< $(CXXFLAGS)

trie_ascii: trie_ascii.c
	$(CC) -o $@ $< $(CFLAGS)

.PHONY:
clean:
	rm -rf trie trie_ascii
	rm -rf *.o
	rm -rf a.out


