#ifndef TABELA_HASH_H
#define TABELA_HASH_H
#include <vector>
#include "pedido.h"
#include "avl.h"

// TABELA HASH - cache de pedidos frequentes (encadeamento separado)
struct NoHash {
    Pedido p;        // cópia rasa: a receita pertence à AVL
    NoHash* prox;
};

struct TabelaHash {
    std::vector<NoHash*> tab;   // vetor de listas
    int m = 0;                  // número de slots (usar primo)
    int n = 0;                  // elementos armazenados
    int capacidade = 0;         // máximo de entradas (política de evicção)
    long hits = 0, misses = 0, colisoes = 0, evicoes = 0;
    double lambda() const { return m > 0 ? (double)n / (double)m : 0.0; }   // fator de carga
};

// Prepara a tabela vazia com m slots e a capacidade máxima do cache
void inicializarHash(TabelaHash& th, int m, int capacidade);

// Insere no cache (início da lista do bucket). Se cheio, evicta a entrada
// mais antiga do bucket. Complexidade O(1) em média
void inserirHash(TabelaHash& th, const Pedido& p);

// Busca no cache; em caso de miss consulta a AVL (acumulando 'comp') e, se achar,
// insere no cache. Retorna nullptr se o pedido não existe
const Pedido* buscarHash(TabelaHash& th, int id, NoAVL* raizAVL, int& comp);

// Libera os nós (NÃO libera receitas: pertencem à AVL). Chamar antes de destruirAVL
void destruirHash(TabelaHash& th);

#endif
