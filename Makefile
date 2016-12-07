CC=g++
CFLAGS=-O3 -std=c++11
OBJS=generate.o genetics.o select.o stats.o
VPATH=src

all: ga-serial ga-parallel

ga-serial: serial.o $(OBJS)
	$(CC) -o $@ $(CFLAGS) $^

ga-parallel: parallel.o $(OBJS)
	$(CC) -o $@ $(CFLAGS) -pthread $^

$(OBJS) serial.o parallel.o: %.o: %.cpp config.h
	$(CC) -o $@ -c $(CFLAGS) $<

test-serial: ga-serial
	time ./ga-serial data/network-small.txt

test-parallel: ga-parallel
	time ./ga-parallel data/network-small.txt

clean:
	rm -f *.o src/*~ net.txt ga-serial ga-parallel

.PHONY: clean
