CC := g++
CFLAGS := -std=c++11

all: trie

trie: trie.cpp trie.h
	$(CC) -o $@ $< $(CFLAGS)

.PHONY:
clean:
	rm -rf trie
	rm -rf *.o


