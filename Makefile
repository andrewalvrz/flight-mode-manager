# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread -I./src

# Source files
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Output binary
BIN = bin/flight_mode_manager

# Default target
all: $(BIN)

# Link object files
$(BIN): $(OBJ)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile cpp -> o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ) $(BIN)
