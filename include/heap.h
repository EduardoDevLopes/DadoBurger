#ifndef HEAP_H
#define HEAP_H

// HEAP MÍNIMO - estoque de ingredientes perecíveis (chave: turnoVencimento)
// ADAPTAÇÕES sobre o esqueleto do grupo: (1) vetor dinâmico próprio no lugar de
// std::vector (o enunciado proíbe contêineres da STL nas estruturas); (2) cada
// preparo produz UMA unidade (§4.7), então o lote perdeu 'quantidade' e o nome em
// string virou o símbolo do ingrediente.
struct Lote {
    char ingrediente;      // 'n' carne, 'o' ovo frito, 'b' bacon
    int turnoVencimento;   // menor turno fica no topo
};

struct Heap {
    Lote* v = nullptr;
    int tam = 0;
    int cap = 0;
};

// Estoque do jogador: um heap por perecível + contadores dos perenes (s, q, c, t)
struct Estoque {
    Heap heaps[3];          // carne, ovo frito, bacon
    int perenes[4] = {0, 0, 0, 0};
};

// Insere lote e reordena via sift-up. Complexidade O(log n)
void inserirLoteHeap(Heap& h, const Lote& l);

// Remove o lote do topo (o que vence primeiro). Retorna false se vazio. O(log n)
bool removerTopoHeap(Heap& h, Lote& out);

// Remove do topo todos os lotes com turnoVencimento <= turnoAtual.
// Custo O(k log n) para k vencidos (não varre o heap inteiro). Retorna k
int removerVencidos(Heap& h, int turnoAtual);

// Heap de um perecível ('n', 'o' ou 'b'); nullptr se o símbolo não é perecível
Heap* heapDoIngrediente(Estoque& e, char simbolo);

// Aplica removerVencidos nos 3 heaps; 'descartados[i]' (opcional) recebe o total de cada um.
// Retorna o total removido
int removerVencidosEstoque(Estoque& e, int turnoAtual, int* descartados = nullptr);

// Libera os vetores dos heaps
void destruirEstoque(Estoque& e);

#endif
