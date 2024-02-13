CC = gcc

CFLAGS = -Wall -Wextra -std=c99

EXECUTABLE = output

SRC = main.c

# Default target: build the executable
all: $(EXECUTABLE)

# Rule to build the executable
$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to clean up generated files
clean:
	rm -f $(EXECUTABLE)
