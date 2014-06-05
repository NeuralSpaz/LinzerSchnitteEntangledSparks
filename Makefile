# build executable
CC = gcc
CFLAGS = -Wall -Werror
LIBS+=-lm

all: steel flint

flint: flint.o sparkfunc.o
	$(CC) $(CFLAGS) -o flint flint.o sparkfunc.o  $(LIBS)

flint.o: flint.c sparkfunc.h
	$(CC) $(CFLAGS) -c -o flint.o flint.c $(LIBS)

sparkfunc.o: sparkfunc.c sparkfunc.h
	$(CC) $(CFLAGS) -c -o sparkfunc.o sparkfunc.c $(LIBS)

steel: steel.o sparkfunc.o
	$(CC) $(CFLAGS) -o steel steel.o sparkfunc.o $(LIBS)

steel.o: steel.c sparkfunc.h
	$(CC) $(CFLAGS) -c -o steel.o steel.c $(LIBS)

clean:
	$(RM) *.o
	$(RM) flint
	$(RM) steel
