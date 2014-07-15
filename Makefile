# build executable
CC = gcc
CFLAGS= -Wall -Werror -O2
LIBS = -lrpigpio
INCLUDES = -Isrc/gpio/include -Lsrc/gpio/library
LDFLAGS= -Lsrc/gpio/library 
SRCDIR=src
OBJS1=$(addprefix $(SRCDIR)/,util.o esp.o esp_time.o udp.o flint.o)
OBJS2=$(addprefix $(SRCDIR)/,util.o esp.o esp_time.o udp.o steel.o i2c_bitbang.o)

all: flint steel

.c.o: 
	$(CC) $(CFLAGS) -c -o $@ $< $(LIBS) $(INCLUDES) $(LDLAGS)

flint: $(OBJS1)
	$(CC) $(CFLAGS) -o $@ $(OBJS1)

steel: $(OBJS2)
	$(CC) $(CFLAGS) -o $@ $(OBJS2) $(LIBS) $(INCLUDES) $(LDLAGS)

clean:
	$(RM) src/*.o


