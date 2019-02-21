
CC=gcc

all:client server
	

client: client.o
	$(CC) -o client client.o

server: server.o common.o
	$(CC) -o $@ server.o common.o

server.o: server.c 
	$(CC) -c -o $@ $<

common.o: common.c
	$(CC) -c -o $@ $<

client.o: client.c 
	$(CC) -c -o $@ $<

.PHONY:
clean:
	rm -rf *.o
	rm -rf client server
