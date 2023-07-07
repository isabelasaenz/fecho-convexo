CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
EXEC = $(BIN_DIR)/fechoconvexo

.PHONY: all clean fecho

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<

clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC)

fecho: $(EXEC)
	$(eval inputfile=$(word 2,$(MAKECMDGOALS)))
	./$(EXEC) $(inputfile)
