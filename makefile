CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -lm
EXECUTABLE = output
SRC = $(wildcard ./src/*.c)  # Use wildcard to capture all .c files in the src directory
INCLUDE_DIR = ./include

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $^

clean:
	rm -f $(EXECUTABLE)

run: $(EXECUTABLE)  # Add a run target to execute the compiled program
	./$(EXECUTABLE)
