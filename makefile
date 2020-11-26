CXX = g++
CXXFLAGS = -Wall

proj3: BST.o Scanner.o driver.cpp
	$(CXX) $(CXXFLAGS) BST.o Scanner.o driver.cpp -o proj3

Scanner.o: BST.o Scanner.h Scanner.cpp
	$(CXX) $(CXXFLAGS) -c Scanner.cpp

BST.o: BST.h BST.cpp
	$(CXX) $(CXXFLAGS) -c BST.cpp

run:
	./proj3

val:
	valgrind ./proj3
