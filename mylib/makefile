LIBRARY_NAME := DynamicArray.a
LIB_BUILD_DIR := ./lib
SRC_DYNAMIC_ARRAY_HANDLER := $(wildcard ../src/array/*.c)
OBJ_DYNAMIC_ARRAY_HANDLER := $(patsubst ../src/array/%.c, $(LIB_BUILD_DIR)/%.o, $(SRC_DYNAMIC_ARRAY_HANDLER))

$(shell mkdir -p $(LIB_BUILD_DIR))

$(LIB_BUILD_DIR)/%.o: ./src/array/%.c $(INC_FILES)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

lib: $(OBJ_DYNAMIC_ARRAY_HANDLER)
	ar rcs $(BUILD_DIR)/$(LIBRARY_NAME) $^

$(BUILD_DIR)/$(EXECUTABLE): $(SRC) $(OBJ_ARRAY) $(BUILD_DIR)/$(LIBRARY_NAME)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $^ $(LDFLAGS)
