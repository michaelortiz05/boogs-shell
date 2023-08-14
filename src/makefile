# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# List of object files to be built
OBJS = main.o parser.o

# Target executable
TARGET = boogsshell

# Default rule to build the target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build the main object file
main.o: main.c parser.h
	$(CC) $(CFLAGS) -c main.c

# Rule to build the parser object file
parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

# Rule to clean up the build directory
clean:
	rm -f $(OBJS) $(TARGET)
