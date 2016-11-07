.PHONY:all
all: server client

obj = server.o client.o
CXXFLAGS = -g -o2 -Wall

server:server.o
	g++ -o server server.o 

client:client.o
	g++ -o client client.o

$(obj):%.o:%.cc
	g++ $(CXXFLAGS) -c $< -o $@

.PHONY:clean
clean:
	-rm -rf $(obj) server client 


