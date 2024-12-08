# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Executable and source files
TARGET = kingdom_expansion
SOURCES = main.cpp graph.cpp
HEADERS = graph.h

# Build target
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean build files
clean:
	rm -f $(TARGET)