##############################################################################
TARGET 			:= test

ROOT			:= $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
SRC_DIR			:= $(ROOT)/src
BUILD_DIR 		:= $(ROOT)/build



SRC 			:= $(wildcard $(SRC_DIR)/*.cpp)
INCLUDE_DIRS 	:= $(SRC_DIR) $(SRC_DIR)/MathLib



##############################################################################
TARGET_ELF := $(BUILD_DIR)/$(TARGET).elf


$(BUILD_DIR): $(SRC)
	@mkdir -p $@
	@echo "compiling $(notdir $^)..."
	@g++ $^ -o $(TARGET_ELF) $(addprefix -I,$(INCLUDE_DIRS))
	

clean:
	@echo "Cleaning $(TARGET)..."
	@rm -rf $(BUILD_DIR)
	@echo "Cleaning $(TARGET) succeeded."
