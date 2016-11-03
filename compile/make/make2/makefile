OBJS = file1.o file2.o
XX = g++
CFLAGS = -o2 -Wall -g
TARGET = helloworld

$(TARGET):$(OBJS)
	g++ $(OBJS) -o $(TARGET)

file2.o: file2.cpp
	g++ $(CFLAGS) -c file2.cpp -o file2.o

file1.o: file1.cpp
	g++  $(CFLAGS) -c file1.cpp -o file1.o

clean:
	rm -rf $(TARGET) $(OBJS)
