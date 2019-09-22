# Change the CXX variable assignment at your own risk.
CXX ?= g++ 
CXXFLAGS=-std=c++11 -Wall 
LDFLAGS=-g

all: clusterBig   

clusterBig: graph.o

graph.o: graph.hpp vertex.hpp   

clean:
	rm -f clusterBig *.o core* *~
