# makefile

# Complier
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Flags
RM = rm -rf

# Deletion Target
TARGET = main
OBJS = main.o MurmurHash.o HyperLogLog.o

# Target executable
main: main.o MurmurHash.o HyperLogLog.o
	$(CXX) $(CXXFLAGS) -o main main.o MurmurHash.o HyperLogLog.o

# Object files
main.o: main.cpp ../includes/MurmurHash.h ../includes/HyperLogLog.h MurmurHash.cpp HyperLogLog.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

HyperLogLog.o: HyperLogLog.cpp ../includes/HyperLogLog.h ../includes/MurmurHash.h
	$(CXX) $(CXXFLAGS) -c HyperLogLog.cpp

MurmurHash.o: MurmurHash.cpp ../includes/MurmurHash.h
	$(CXX) $(CXXFLAGS) -c MurmurHash.cpp

# run
run:
	./$(TARGET)

# clean up
clean:
	$(RM) $(TARGET) $(OBJS)