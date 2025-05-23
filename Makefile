CXX = g++
CXXFLAGS = -Wall -std=c++17
OUTPUT = main

$(OUTPUT): main.cpp
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) main.cpp