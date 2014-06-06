# build executable
CC = gcc
CFLAGS = -Wall -Werror
LIBS+=-lm
LIBS2+= -Igpio/include -Lgpio/library -lrpigpio
all: steel flint

flint: flint.o sparkfunc.o
	$(CC) $(CFLAGS) -o flint flint.o sparkfunc.o  $(LIBS)

flint.o: flint.c sparkfunc.h
	$(CC) $(CFLAGS) -c -o flint.o flint.c $(LIBS)

sparkfunc.o: sparkfunc.c sparkfunc.h
	$(CC) $(CFLAGS) -c -o sparkfunc.o sparkfunc.c $(LIBS)

steel: steel.o sparkfunc.o i2c_bitbang.o i2c_bitbang.o
	$(CC) $(CFLAGS) -o steel steel.o sparkfunc.o i2c_bitbang.o $(LIBS2) $(LIBS)

steel.o: steel.c sparkfunc.h i2c_bitbang.h 
	$(CC) $(CFLAGS) -c -o steel.o steel.c $(LIBS2) $(LIBS)

i2c_bitbang.o: i2c_bitbang.c i2c_bitbang.h
	./make-rPi-GPIO.sh
	$(CC) $(CFLAGS) -c -o i2c_bitbang.o i2c_bitbang.c $(LIBS2) $(LIBS)


clean:
	$(RM) *.o
	$(RM) flint
	$(RM) steel
