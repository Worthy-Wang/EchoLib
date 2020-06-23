#版本三
CC=g++
CFLAGS=-g -Wall
target=app
src=$(wildcard *.cpp)
obj=$(patsubst %.cpp, %.o, $(src))
link=-lpthread
$(target):$(obj)
	$(CC) $(CFLAGS)  $^ -o $@ $(link)
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(link)
clean:
	rm -rf $(target) $(obj)
