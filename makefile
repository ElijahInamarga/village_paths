CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = kingdom_expansion
SRC = main.cpp graph.cpp graph.h input.txt

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)