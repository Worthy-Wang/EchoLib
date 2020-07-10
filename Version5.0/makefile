#版本三
CC=g++
CFLAGS=-g -Wall
target=server
src=$(wildcard *.cpp) $(wildcard ./net/*.cpp) $(wildcard ./threadpool/*.cpp)
obj=$(patsubst %.cpp, %.o, $(src))
link=-lpthread
$(target):$(obj)
	$(CC) $(CFLAGS)  $^ -o $@ $(link)
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(link)
clean:
	rm -rf $(target) $(obj)
