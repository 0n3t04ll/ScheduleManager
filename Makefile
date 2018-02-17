CXX=g++
CXXFLAGS=-g3 -std=c++0x

all:test
test:test.o scheduler.o
	$(CXX) -o test test.o scheduler.o; rm -rf *.o 2> /dev/null

test.o:test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp 

scheduler.o:scheduler.cpp 
	$(CXX) $(CXXFLAGS) -c scheduler.cpp
	

clean:
	rm -rf *.o
