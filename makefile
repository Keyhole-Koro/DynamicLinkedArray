CC = gcc
CFLAGS = -Wall -Wextra -std=c99
EXECUTABLE = output
SRC = ./src/main.c
INCLUDE_DIR = ./include

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $^

clean:
	rm -f $(EXECUTABLE)
