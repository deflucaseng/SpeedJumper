SRCS := $(shell find . -name "*.cpp")
OBJS := $(SRCS:.cpp=.o)
TARGET := program

CXX := g++
CXXFLAGS := -std=c++17 -Wall

.PHONY: representation all run

representation:
	python3 scripts/representation.py

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)