# build executable
CC = gcc
CFLAGS += -Wall -Werror
LIBS+=
LIBS2+= -Igpio/include -Lgpio/library -lrpigpio

all: tests.o esp.o util.o esp_time.o udp.o flint.o steel.o
	$(CC) $(CFLAGS) -o tests tests.o esp.o util.o esp_time.o $(LIBS)
	$(CC) -o flint flint.o esp.o util.o esp_time.o udp.o $(LIBS)
	$(CC) -o steel steel.o esp.o util.o esp_time.o udp.o $(LIBS)
	cp tests ../
	cp flint ../
	cp steel ../

flint.o: flint.c
	$(CC) $(CFLAGS) -c -o flint.o flint.c $(LIBS)

steel.o: steel.c
	$(CC) -c -o steel.o steel.c $(LIBS)

tests.o: tests.c
	$(CC) $(CFLAGS) -c -o tests.o tests.c $(LIBS)

esp.o: esp.c esp.h
	$(CC) $(CFLAGS) -c -o esp.o esp.c $(LIBS)

util.o: util.c util.h
	$(CC) $(CFLAGS) -c -o util.o util.c $(LIBS)

esp_time.o: esp_time.c esp_time.h
	$(CC) $(CFLAGS) -c -o esp_time.o esp_time.c $(LIBS)

udp.o: udp.c udp.h
	$(CC) $(CFLAGS) -c -o udp.o udp.c $(LIBS)

clean:
	$(RM) *.o
	$(RM) tests
	$(RM) steel
	$(RM) flint
	$(RM) ../tests
	$(RM) ../steel
	$(RM) ../flint
