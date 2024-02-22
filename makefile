CC = clang
LD = lld
CFLAGS = -Wall -Wextra -std=c99 -lm
LDFLAGS = -fuse-ld=$(LD)
EXECUTABLE = output
SRC = $(wildcard ./src/*.c)
INCLUDE_DIR = ./inc
BUILD_DIR = ./build

# Find all header files in inc directory
INC_FILES := $(wildcard ./inc/*.h)

all: $(BUILD_DIR)/$(EXECUTABLE)

$(BUILD_DIR)/$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $(foreach INC,$(INC_FILES),-include $(INC)) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(BUILD_DIR)/$(EXECUTABLE)

run: $(BUILD_DIR)/$(EXECUTABLE)
	./$(BUILD_DIR)/$(EXECUTABLE)
