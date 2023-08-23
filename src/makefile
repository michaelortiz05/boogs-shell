# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# List of object files to be built
OBJS = main.o lexer.o

# Target executable
TARGET = boogsshell

# Default rule to build the target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build the main object file
main.o: main.c lexer.h
	$(CC) $(CFLAGS) -c main.c

# Rule to build the lexer object file
lexer.o: lexer.c lexer.h
	$(CC) $(CFLAGS) -c lexer.c

# Rule to clean up the build directory
clean:
	rm -f $(OBJS) $(TARGET)