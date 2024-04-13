CC = clang
LD = lld
CFLAGS = -Wall -Wextra -std=c99 -lm
LDFLAGS = -fuse-ld=$(LD)
EXECUTABLE = output
SRC = $(wildcard ./src/*.c) $(wildcard ./src/**/*.c)
INC := $(wildcard ./inc/*.h)

INCLUDE_DIR = ./inc
BUILD_DIR = ./build

$(shell mkdir -p $(BUILD_DIR))

all: $(BUILD_DIR)/$(EXECUTABLE)

$(BUILD_DIR)/$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(BUILD_DIR)/$(EXECUTABLE)

run: $(BUILD_DIR)/$(EXECUTABLE)
	./$(BUILD_DIR)/$(EXECUTABLE)
