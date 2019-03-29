
CFLAGS= -Wall -Wextra -DDEBUG -g -std=c++14

all: lab6

lab6: lab6.o
	g++ $(CFLAGS) lab6.o -o lab6

lab6.o: lab6.cpp BSTree.h
	g++ $(CFLAGS) -c lab6.cpp

run: all
	./lab6

clean:
	rm -rf lab6 *.o
memcheck:
	valgrind ./lab6
