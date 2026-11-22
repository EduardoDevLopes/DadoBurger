# Dado Burger - INF01203 (UFRGS)
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Iinclude
# nome do enunciado; o executável fica na raiz, junto dos arquivos de entrada
BIN      := dado_burger

SRC      := $(wildcard src/*.cpp)
OBJ      := $(patsubst src/%.cpp,build/%.o,$(SRC))
LIB_OBJ  := $(filter-out build/main.o,$(OBJ))

PEDIDOS   ?= pedidos/pedidos.txt
HISTORICO ?= historico/historico.txt

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

build:
	mkdir -p build

run: $(BIN)
	./$(BIN) $(PEDIDOS) $(HISTORICO)

test: $(LIB_OBJ) tests/testes.cpp
	$(CXX) $(CXXFLAGS) -o build/testes tests/testes.cpp $(LIB_OBJ)
	./build/testes

bench: $(LIB_OBJ) tests/bench.cpp
	$(CXX) $(CXXFLAGS) -o build/bench tests/bench.cpp $(LIB_OBJ)
	@echo "Uso: ./build/bench ord historico.txt | hash | rot"

# Verifica vazamentos de memória (exigido na entrega); usa uma cópia do histórico
leaks: $(BIN)
	cp $(HISTORICO) build/historico_leaks.txt
	printf '1\nTeste\np c\ns\n3\n1\n4\n' | valgrind --leak-check=full --error-exitcode=1 ./$(BIN) $(PEDIDOS) build/historico_leaks.txt

# Alternativa ao valgrind: AddressSanitizer + UBSan
asan:
	$(CXX) -std=c++17 -g -fsanitize=address,undefined -Iinclude -o build/dado_burger_asan src/*.cpp

relatorio:
	cd relatorio && pdflatex -interaction=nonstopmode relatorio.tex && pdflatex -interaction=nonstopmode relatorio.tex

# Pacote do Moodle: fontes e cabeçalhos no MESMO diretório (comando do Apêndice C)
entrega: relatorio/relatorio.pdf medicoes.log
	rm -rf entrega && mkdir -p entrega/tp-grupoX
	cp src/*.cpp include/*.h include/*.hpp entrega/tp-grupoX/
	cp relatorio/relatorio.pdf medicoes.log entrega/tp-grupoX/
	printf '%s\n' "g++ -o dado_burger *.cpp -Wall -std=c++17" "./dado_burger pedidos.txt historico.txt" > entrega/tp-grupoX/COMPILAR.txt
	cd entrega && zip -qr tp-grupoX.zip tp-grupoX
	@echo "Gerado: entrega/tp-grupoX.zip (renomeie com o numero do grupo)"

clean:
	rm -rf build $(BIN) entrega

-include $(OBJ:.o=.d)
.PHONY: all run test bench leaks asan relatorio entrega clean
