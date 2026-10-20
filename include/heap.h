#ifndef HEAP_H
#define HEAP_H
#include <string>
#include <vector>

// HEAP MÍNIMO - lotes perecíveis (chave: turnoVencimento)
struct Lote {
    std::string ingrediente;
    int quantidade;
    int turnoVencimento;   // menor turno fica no topo
};

// Um heap por ingrediente perecível
struct Estoque {
    std::vector<std::string> nomes;
    std::vector<std::vector<Lote>> heaps;   // heaps[i] pertence a nomes[i]
};

// Insere lote e reordena via sift-up. Complexidade O(log n)
void inserirLoteHeap(std::vector<Lote>& h, const Lote& l);

// Remove o lote do topo (o que vence primeiro). Retorna false se vazio. O(log n)
bool removerTopoHeap(std::vector<Lote>& h, Lote& out);

// Remove do topo todos os lotes com turnoVencimento <= turnoAtual.
// Custo O(k log n) para k vencidos (não varre o heap inteiro). Retorna k
int removerVencidos(std::vector<Lote>& h, int turnoAtual, std::vector<Lote>* removidos = nullptr);

// Devolve (criando se preciso) o heap de um ingrediente
std::vector<Lote>& heapDoIngrediente(Estoque& e, const std::string& nome);

// Aplica removerVencidos em todos os ingredientes; retorna total removido
int removerVencidosEstoque(Estoque& e, int turnoAtual);

#endif
