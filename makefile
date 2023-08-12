CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11 -Iinclude

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
DATA_DIR := data

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

TARGET := $(BIN_DIR)/spell_checker

DATA_FILES := $(wildcard $(DATA_DIR)/*)

.PHONY: all clean

all: $(TARGET) data

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BIN_DIR)/dict.txt: $(DATA_DIR)/dict.txt
	copy $(DATA_DIR)\dict.txt $(BIN_DIR)\dict.txt

$(BIN_DIR)/freq.txt: $(DATA_DIR)/freq.txt
	copy $(DATA_DIR)\freq.txt $(BIN_DIR)\freq.txt

$(BIN_DIR):
	mkdir $(BIN_DIR)

data: $(BIN_DIR) $(DATA_FILES:$(DATA_DIR)/%=$(BIN_DIR)/%)

clean:
	del /q $(BUILD_DIR)\* $(BIN_DIR)\*

clean-all: clean
	del /q $(DATA_DIR)\*

