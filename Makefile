## This is a simple Makefile

# Define what compiler to use and the flags.
CXX=g++
CXXFLAGS= -g -std=c++0x -Wall -Werror


all: proj2

# Compile all .c files into .o files
# % matches all (like * in a command)
# $< is the source file (.c file)
%.o : %.cpp %.h
	$(CXX) -c $(CXXFLAGS) $<


proj2: proj2.o
	$(CXX) -o proj2 proj2.o -lm


clean:
	rm -f *.o proj2