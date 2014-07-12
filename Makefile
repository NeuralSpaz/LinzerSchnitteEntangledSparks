# build executable
CC = gcc
CFLAGS += -Wall -Werror
LIBS+=
LIBS2+= -Igpio/include -Lgpio/library -lrpigpio
all: tests 

tests: tests.o esp.o
	$(CC) $(CFLAGS) -o tests.o esp.o  $(LIBS)

esp.o: esp.c esp.h
	$(CC) $(CFLAGS) -c -o esp.c $(LIBS)

clean:
	$(RM) *.o
