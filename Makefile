UNAME_S := $(shell uname -s)

CC=gcc
CFLAGS=-std=c99
# DEBUGGING

ifndef DEBUG
	DEBUG = 1
endif

ifeq ($(DEBUG), 1)
	CFLAG+=-g -O0
else
	CFLAGS+=-O3
endif

# force x86_64 architecture on MAC OS X; read minjem mas Didiet
ifeq ($(UNAME_S), Darwin)
	CC=clang
	CFLAGS+=-arch x86_64
endif

SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)

TARGETS=build/debe.exe

all: $(TARGETS)

$(TARGETS): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(TARGETS)

.PHONY: all clean

