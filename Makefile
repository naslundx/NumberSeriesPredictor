CC=g++

CFLAGS=-c -Wall -std=c++0x

all:numberseriespredictor

numberseriespredictor: numberseriespredictor.o genotype.o population.o
		$(CC) numberseriespredictor.o genotype.o population.o -o numberseriespredictor

numberseriespredictor.o: numberseriespredictor.cpp
		$(CC) $(CFLAGS) numberseriespredictor.cpp

genotype.o: genotype.cpp
		$(CC) $(CFLAGS) genotype.cpp

population.o: population.cpp
		$(CC) $(CFLAGS) population.cpp

clean:
		rm -rf *o numberseriespredictor
