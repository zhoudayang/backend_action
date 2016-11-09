.PHONY:all
all:server client

CXXFLAGS = -g -Wall -std=c++11 -o2

server:server.o
	g++ -o server server.o

client:client.o
	g++ -o client client.o

.PHONY:clean

clean:
	-rm -rf *.o client server 

