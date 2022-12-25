CFLAGS=-g
CC=gcc

PROG=build

all: $(PROG)

install: $(PROG)
	install $(PROG) $(HOME)/bin/

LIBS= 

build:
	$(CC) $(LIBS) src/*.c -o gpm.o

clean:
	rm gpm.o tmp
