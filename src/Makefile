# build executable
CC = gcc
CFLAGS += -Wall -Werror
LIBS+=
LIBS2+= -Igpio/include -Lgpio/library -lrpigpio

all: tests.o esp.o util.o
	$(CC) -o unittests tests.o esp.o util.o $(LIBS)

tests.o: tests.c
	$(CC) $(CFLAGS) -c -o tests.o tests.c $(LIBS)

esp.o: esp.c esp.h
	$(CC) $(CFLAGS) -c -o esp.o esp.c $(LIBS)

util.o: util.c util.h
	$(CC) $(CFLAGS) -c -o util.o util.c $(LIBS)

clean:
	$(RM) *.o
	$(RM) unittests
