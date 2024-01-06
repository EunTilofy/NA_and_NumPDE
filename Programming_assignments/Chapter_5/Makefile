CXX = g++
CXXFLAGS = -std=c++20 -Iinclude
BUILD_DIR = build

$(shell mkdir -p $(BUILD_DIR))

CPP_SOURCES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix $(BUILD_DIR)/, $(CPP_SOURCES:.cpp=.o))

INCLUDE_SOURCES := $(wildcard include/serialization/**/*.cpp)
INCLUDE_OBJ_FILES := $(addprefix $(BUILD_DIR)/, $(INCLUDE_SOURCES:.cpp=.o))

define make-dependency-dir
	@mkdir -p $(dir $1)
endef

all: solAB solC

solAB: $(INCLUDE_OBJ_FILES) $(BUILD_DIR)/Problem-AB.o
	$(CXX) $(CXXFLAGS) $^ -o $@

solC: $(INCLUDE_OBJ_FILES) $(BUILD_DIR)/Problem-C.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp
	$(call make-dependency-dir,$@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) solAB solC

run:
	./solAB data/dataAB.json
	./solC data/dataAB.json 2>data/resC.txt

.PHONY: all clean
