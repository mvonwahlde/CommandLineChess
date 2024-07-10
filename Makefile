# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Target executable
TARGET = chess.exe

# Source files
SRCS = main.cpp Board.cpp Game_Pieces\Piece.cpp Game_Pieces\Empty.cpp Game_Pieces\Pawn.cpp Game_Pieces\Knight.cpp Game_Pieces\Bishop.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Build target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run target
run: $(TARGET)
	./$(TARGET)

# Clean target
clean:
	del $(OBJS) $(TARGET)
#rm $(TARGET)

# Phony targets
.PHONY: all run clean