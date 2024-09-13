# Define the compiler
CXX = g++

# Define compiler flags
CXXFLAGS = -std=c++17 -Iinclude

# Define the target executable
TARGET = build/PolyProject

# Define the source files
SRCS = src/main.cpp src/ui.cpp src/utils.cpp src/NGram.cpp src/line.cpp src/point.cpp

# Define the object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -O3

# Rule to clean up generated files
clean:
	rm -f $(OBJS)
#	rm -f $(TARGET) $(OBJS)
