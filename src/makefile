# makefile

# Complier
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Flags
RM = rm -rf

# Deletion Target
TARGET = main
OBJS = main.o MurmurHash.o

# Target executable
main: main.o MurmurHash.o
	$(CXX) $(CXXFLAGS) -o main main.o MurmurHash.o

# Object files
main.o: main.cpp ../includes/MurmurHash.h
	$(CXX) $(CXXFLAGS) -c main.cpp

MurmurHash.o: MurmurHash.cpp ../includes/MurmurHash.h
	$(CXX) $(CXXFLAGS) -c MurmurHash.cpp

# run
run:
	./$(TARGET)

# clean up
clean:
	$(RM) $(TARGET) $(OBJS)