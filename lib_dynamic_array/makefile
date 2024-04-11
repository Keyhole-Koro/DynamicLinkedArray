CC = clang
LD = lld
CFLAGS = -Wall -Wextra -std=c99 -lm
LDFLAGS = -fuse-ld=$(LD)
SRC = $(wildcard ../src/*.c) $(wildcard ../src/**/*.c)
INC := $(wildcard ../inc/*.h)
INCLUDE_DIR = ../inc
BUILD_DIR = ./lib

TARGET_NAME = DynamicArrayHandler
LIBRARY_NAME = DynamicArray

BUILT_OBJ = $(BUILD_DIR)/$(TARGET_NAME).o

$(shell mkdir -p $(BUILD_DIR))

$(BUILT_OBJ): ../src/array/$(TARGET_NAME).c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $^ $(LDFLAGS)

lib: $(BUILT_OBJ)
	ar rcs $(BUILD_DIR)/$(LIBRARY_NAME).a $^

clean:
	rm -f $(BUILD_DIR)/$(LIBRARY_NAME).a

.PHONY: lib