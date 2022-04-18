## This is a simple Makefile

# Define what compiler to use and the flags.

all: proj2

# Compile all .c files into .o files
# % matches all (like * in a command)
# $< is the source file (.c file)
# %.o : %.cpp %.h
#	$(CXX) -c $(CXXFLAGS) $<

Simulation.o: Simulation.cpp Simulation.h
	g++ -c Simulation.cpp

proj2: Simulation.o proj2.o
	g++ -o proj2 Simulation.o proj2.o 

proj2.o: proj2.cpp
	g++ -c proj2.cpp

clean:
	rm -f *.o proj2