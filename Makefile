# Makefile

OBJS = main.o hailstone.o
CC = g++
CFLAGS = -Wall -c -std=c++0x
LFLAGS = -Wall

all: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o hailstone

#hailstone : main.o hailstone.o
#	g++ main.o hailstone.o -o hailstone

main.o : main.cpp hailstone.h
	$(CC) $(CFLAGS) main.cpp

hailstone.o : hailstone.cpp hailstone.h
	$(CC) $(CFLAGS) hailstone.cpp

clean: 
	rm *.o hailstone

tar:
	tar -zcvf hailstone.tar.gz Makefile *.cpp *.h
