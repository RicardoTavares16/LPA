# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall -lm -ansi -Wpedantic

# the build target executable:
TARGET = main
RM = rm -f

all: $(TARGET)

$(TARGET):
	$(RM) $(TARGET).out
	$(CC) $(TARGET).c -o $(TARGET).out $(CFLAGS)

run:
	./$(TARGET).out

clean:
	$(RM) $(TARGET).out
