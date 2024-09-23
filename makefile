# Define the compiler
CXX = g++

# Define compiler flags
CXXFLAGS = -std=c++17 -Iinclude -O3

# Define the target executable
TARGET = build/PolyProject

# Define the source files explicitly
SRCS = src/main.cpp src/ui.cpp src/utils.cpp src/NGram.cpp src/NGramLineApproach.cpp src/NGramPolyApproach.cpp src/line.cpp src/point.cpp src/Timer.cpp src/Connection.cpp src/Polygon.cpp

# Define the object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)
