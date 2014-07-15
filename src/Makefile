# build executable
CC = gcc
CFLAGS += -Wall -Werror -O
LIBS+=
LIBS2+= -Igpio/include -Lgpio/library -lrpigpio

all: tests.o esp.o util.o esp_time.o udp.o flint.o steel.o i2c_bitbang.o
	$(CC) $(CFLAGS) -o tests tests.o esp.o util.o esp_time.o udp.o $(LIBS)
	$(CC) $(CFLAGS) -o flint flint.o esp.o util.o esp_time.o udp.o $(LIBS)
	$(CC) $(CFLAGS) -o steel steel.o esp.o util.o esp_time.o udp.o i2c_bitbang.o $(LIBS) $(LIBS2)


flint.o: flint.c
	$(CC) $(CFLAGS) -c -o flint.o flint.c $(LIBS)

steel.o: steel.c
	$(CC) $(CFLAGS) -c -o steel.o steel.c $(LIBS) $(LIBS2)

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

i2c_bitbang.o: i2c_bitbang.c i2c_bitbang.h
	./make-rPi-GPIO.sh
	$(CC) $(CFLAGS) -c -o i2c_bitbang.o i2c_bitbang.c $(LIBS2) $(LIBS)

clean:
	$(RM) *.o
	$(RM) tests
	$(RM) steel
	$(RM) flint
	$(RM) ../tests
	$(RM) ../steel
	$(RM) ../flint
	./clean-rPi-GPIO.sh
