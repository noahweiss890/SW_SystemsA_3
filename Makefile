CC = gcc
AR = ar
FLAGS = -Wall -g
OBJECTS = main.o string_funcs.o

all: stringProg
stringProg: $(OBJECTS) libstring_funcs.a
	$(CC) $(FLAGS) -o stringProg $(OBJECTS) libstring_funcs.a
libstring_funcs.a: string_funcs.o
	$(AR) -rcs libstring_funcs.a string_funcs.o
main.o: main.c string_funcs.h
	$(CC) $(FLAGS) -c main.c
string_funcs.o: string_funcs.c string_funcs.h
	$(CC) $(FLAGS) -c string_funcs.c
.PHONY: all clean
clean:
	rm -f stringProg *.o *.a