# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -std=c++17 -Wall -Wextra

# the build target executable:
TARGET = main
RM = rm -f

all: $(TARGET)

$(TARGET):
	$(RM) $(TARGET).out
	$(CC) $(TARGET).cpp -o $(TARGET).out $(CFLAGS)

run:
	./$(TARGET).out

clean:
	$(RM) $(TARGET).out
