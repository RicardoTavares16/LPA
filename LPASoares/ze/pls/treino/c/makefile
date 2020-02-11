# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall -ansi -lm -std=c99

# the build target executable:
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(RM) $(TARGET)
	$(CC) $(TARGET).c -o $(TARGET) $(CFLAGS)
	./$(TARGET)

run:
	./$(TARGET)
