CXX = g++
CXXFLAGS = -g -Wall -Wextra
TESTFLAGS = -Wa,-mbig-obj

.PHONY : all clean
all : library test

library : hashTable.o library.o book.o main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

test : testCases.cpp hashTable.o library.o book.o 
	$(CXX) $(CXXFLAGS) $(TESTFLAGS) -o $@ $^

hashTable.o : hashTable.cpp hashTable.h
	$(CXX) $(CXXFLAGS) -c $<

library.o : library.cpp library.h
	$(CXX) $(CXXFLAGS) -c $<

book.o : book.cpp book.h
	$(CXX) $(CXXFLAGS) -c $<

clean :
	rm *.o
	rm *.exe
