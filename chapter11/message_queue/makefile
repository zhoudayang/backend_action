.PHONY:all
all:sender receiver

CXXFLAGS = -o2 -std=c++11 -Wall -g 

sender:sender.o
	g++ -o sender sender.o

receiver:receiver.o
	g++ -o receiver receiver.o 

.PHONY:clean
clean:
	-rm -rf *.o sender receiver
