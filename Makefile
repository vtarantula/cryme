# Compiler and compiler options
# CC = clang++
CC = g++
INC = -I include
CC_FLAGS = -std=c++20 -g $(INC) -Wall -Wextra

# File names
CURRENT_DIR := $(shell basename $(CURDIR))

EXEC = $(CURRENT_DIR)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(OBJECTS)
	rm -f $(EXEC)
