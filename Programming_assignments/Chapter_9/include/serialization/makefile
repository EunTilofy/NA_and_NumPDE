CXX = g++
CXXFLAGS = -std=c++20 -Iinclude

SRC_DIR = .
BUILD_DIR = build

# 添加json/json.cpp到SRCS
SRCS = $(wildcard $(SRC_DIR)/*.cpp) xml/tinyxml2.cpp json/jsoncpp.cpp
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
