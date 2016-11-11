.PHONY:all

all:simple_pipe pipe_reader pipe_writer

CXXFLAGS = -g -o2 -std=c++11 -Wall

simple_pipe:pipe.o
	g++ -o simple_pipe pipe.o

pipe_reader:pipe_reader.o
	g++ -o pipe_reader pipe_reader.o

pipe_writer:pipe_writer.o
	g++ -o pipe_writer pipe_writer.o


.PHONY:clean
clean:
	-rm -rf *.o simple_pipe pipe_reader pipe_writer
