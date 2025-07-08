PROJECT_NAME=NeuraNova
BUILD_DIR=build

all: $(BUILD_DIR)/$(PROJECT_NAME)

$(BUILD_DIR)/$(PROJECT_NAME):
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && make

run: all
	./$(BUILD_DIR)/$(PROJECT_NAME)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean run