CFLAGS=-g
CC=gcc

PROG=build

build-pr:
	$(CC) $(LIBS) src/error-handling.c src/profile-reader.c -o profile-reader.o

all: $(PROG)

install: $(PROG)
	install $(PROG) $(HOME)/bin/

LIBS= 

build:
	$(CC) $(LIBS) src/*.c -o gpm.o

clean:
	rm gpm.o tmp
