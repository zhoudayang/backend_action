.PHNOY:all
all:client server

obj = client.o server.o util.o

client:util.o client.o
	g++ -o client client.o util.o

server:server.o util.o
	g++ -o server server.o util.o

.PHONY:clean
clean:
	-rm -rf $(obj) client server
