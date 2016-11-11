.PHONY:all
all:reader writer

reader:reader.o
	g++ -o reader reader.o

writer:writer.o
	g++ -o writer writer.o

CXXFLAGS=-g -o2 -Wall

.PHONY:clean
clean:
	-rm -rf *.o reader writer
