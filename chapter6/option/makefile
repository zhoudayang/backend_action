obj = server.o client.o
.PHONY:all
CXXFLAGS = -g -o2 -Wall 
all:client server

$(obj):%.o:%.cc
	g++ -c $(CXXFLAGS) $< -o $@

client:client.o
	g++ -o client client.o

server:server.o
	g++ -o server server.o

.PHONY:clean
clean:
	-rm -rf $(obj) client server 
