.PHONY:all
all:consumer producer

consumer:consumer.o
	g++ -o consumer consumer.o

producer:producer.o
	g++ -o producer producer.o 

CXXFLAGS = -g -Wall -Werror -o2

.PHONY:clean
clean:
	-rm -rf *.o producer consumer

