cc = gcc
XX = g++
CFLAGS = -Wall -O2 -g
TARGET = helloworld

# 对每一个.c文件，使用gcc进行编译，生成.o文件
%.o: %.c
	$(cc) $(CFLAGS) -c $< -o $@
# 对每一个cpp文件，使用g++进行编译，生成.o文件
%.o: %.cpp
	$(XX) $(CFLAGS) -c $< -o $@

# 使用wildcard函数在 $()内部使用通配符
SOURCES = $(wildcard *.c *.cpp)
# $(patsubst %.c,%.o,$(dir)) 使用patsubst函数将$(dir)中的所有变量符合后缀是.c的文件全部替换成.o文件。
# 下面的函数表示将文件列表中所有的.c和.cpp字符变成.o文件，形成一个新的文件列表，然后存入$(OBJS)变量
OBJS= $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))

$(TARGET) : $(OBJS)
	$(XX) $(OBJS) -o $(TARGET)

clean:
	rm -rf *.o helloworld
