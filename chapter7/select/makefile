.PHONY:all
all:server client

CXXFLAGS = -g -o2 -Wall -std=c++11


server:server.o
	g++ -o server server.o

client:client.o
	g++ -o client client.o


.PHONY:clean
clean:
	-rm -rf *.o server client 
