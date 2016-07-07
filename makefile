all: server client

server: server.c queue.h
	gcc -o server server.c -lpthread

client: client.c
	gcc -o client client.c
