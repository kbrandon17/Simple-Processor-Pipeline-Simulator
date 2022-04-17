## This is a simple Makefile

# Define what compiler to use and the flags.
CC=cc
CXX=CC
CCFLAGS= -g -std=c99 -Wall -Werror


all: proj2

# Compile all .c files into .o files
# % matches all (like * in a command)
# $< is the source file (.c file)
%.o : %.cpp %.h
	$(CC) -c $(CCFLAGS) $<


proj2:
	$(CC) -o proj2 -lm


clean:
	rm -f *.o proj2