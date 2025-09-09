# Existing variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
SRC_DIR = src
TEST_DIR = test

# Sources for main compiler
MAIN_SOURCES = $(SRC_DIR)/lexer.cpp $(SRC_DIR)/parser.cpp \
               $(SRC_DIR)/semantic.cpp $(SRC_DIR)/codegen.cpp \
               $(SRC_DIR)/utils.cpp $(TEST_DIR)/main.cpp

# Sources for semantic tests
TEST_SOURCES = $(SRC_DIR)/lexer.cpp $(SRC_DIR)/parser.cpp \
               $(SRC_DIR)/semantic.cpp $(SRC_DIR)/codegen.cpp \
               $(SRC_DIR)/utils.cpp $(TEST_DIR)/semantic_test.cpp

# Targets
all: compiler semantic_test

compiler: $(MAIN_SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@

semantic_test: $(TEST_SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f compiler semantic_test $(SRC_DIR)/*.o $(TEST_DIR)/*.o

.PHONY: all clean