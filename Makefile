TARGET := ProbabilityCalculator.exe

CXX    := c++
LINKER := c++

CXXFLAGS := -Werror -Wall -Wextra -std=c++23 -O3
LFLAGS   := -Wall 

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

INCLUDES  := ./Lud_Utils/include ./include
LIBRARIES :=

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

dir_guard = @mkdir -p $(@D)


all: directories $(BIN_DIR)/$(TARGET)
	
$(BIN_DIR)/$(TARGET): $(OBJECTS) 
	$(LINKER) -o $@ $(LFLAGS) $^ $(addprefix -l, $(LIBRARIES))
	@echo "Linking complete!"

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp 
	$(CXX) -o $@ -c $(CXXFLAGS) $<  $(addprefix -I, $(INCLUDES))
	@echo "Compiled $< successfully!"

directories: $(BIN_DIR) $(OBJ_DIR)

$(BIN_DIR):
	mkdir $@
	@echo "Created $@ directory!"

$(OBJ_DIR):
	mkdir $@
	@echo "Created $@ directory!"


.phony: clean
clean:
	rm -f $(OBJECTS)
	@echo "removed objects"

.phony: remove
remove:
	rm -rf $(OBJ_DIR)
	@echo "removed objects"
	rm -rf $(BIN_DIR)
	@echo "removed target"