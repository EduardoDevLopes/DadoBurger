# Dado Burger - INF01203 (UFRGS)
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -g

SRC      := $(wildcard src/*.cpp)
OBJ      := $(patsubst src/%.cpp,build/%.o,$(SRC))
LIB_OBJ  := $(filter-out build/main.o,$(OBJ))
TARGET   := build/dadoburger

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

build:
	mkdir -p build

run: $(TARGET)
	./$(TARGET)

test: $(LIB_OBJ) tests/testes.cpp
	$(CXX) $(CXXFLAGS) -o build/testes tests/testes.cpp $(LIB_OBJ)
	./build/testes

# Verifica vazamentos de memória (exigido na entrega)
leaks: $(TARGET)
	valgrind --leak-check=full --error-exitcode=1 ./$(TARGET)

clean:
	rm -rf build

-include $(OBJ:.o=.d)
.PHONY: all run test leaks clean
