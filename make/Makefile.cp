#make the square program
all: square testpstack

#compiler define
CC = gcc

#options for development
CFLAGS = -g -Wall -ansi

#file placs
INCLUDE = .

square: pstack.o
	$(CC) -o square square.c pstack.o


testpstack: pstack.o
	$(CC) -o testpstack testPstack.c pstack.o

testpstack.o: testPstack.c pstack.h
	$(CC) $(CFLAGS) -c testPstack.c

pstack.o: pstack.c pstack.h 
	$(CC) -I$(INCLUDE) $(CFLAGS) -c pstack.c pstack.h

clean:
	-rm square testpstack pstack.o

