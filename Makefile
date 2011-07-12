CC=gcc
OBJECTS=main.o machine.o
CFLAGS=-O3 -g -Wall
OUTPUT=compiler

all: compiler

compiler: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(OUTPUT)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o compiler *~
