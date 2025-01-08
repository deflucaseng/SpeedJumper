# Compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++20 -O2 -I./include -lfmt -g

# Directory settings
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = object
EXE_DIR = exe

# Source files
MAIN = main.cpp
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
ALL_SRCS = $(MAIN) $(SRC_FILES)

# Object files
MAIN_OBJ = $(OBJ_DIR)/main.o
SRC_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
ALL_OBJS = $(MAIN_OBJ) $(SRC_OBJS)

# Executable name
EXEC = $(EXE_DIR)/speedjumper

# Make sure directories exist
$(shell mkdir -p $(OBJ_DIR) $(EXE_DIR))

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(ALL_OBJS)
	$(CXX) $^ -o $@ $(CXXFLAGS)

# Compile main.cpp
$(OBJ_DIR)/main.o: $(MAIN)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@



# Clean build files
clean:
	rm -rf $(OBJ_DIR)/* $(EXE_DIR)/*

.PHONY: all clean representation run


representation:
	python3 ../scripts/representation.py



