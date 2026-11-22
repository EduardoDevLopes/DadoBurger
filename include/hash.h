#ifndef HASH_H
#define HASH_H
#include "pedido.h"
#include "avl.h"

// TABELA HASH - cache de pedidos (encadeamento separado)
// ADAPTAÇÕES: renomeada para hash.* (nome do enunciado); vetor próprio no lugar de
// std::vector; buscarHash passa a acumular as métricas de busca da AVL (EstatAVL).
struct NoHash {
    Pedido p;        // cópia rasa: a receita pertence à AVL
    NoHash* prox;
};

struct TabelaHash {
    NoHash** tab = nullptr;     // vetor de listas
    int m = 0;                  // número de slots (usar primo)
    int n = 0;                  // elementos armazenados
    int capacidade = 0;         // máximo de entradas (política de evicção)
    long hits = 0, misses = 0, colisoes = 0, evicoes = 0;
    double lambda() const { return m > 0 ? (double)n / (double)m : 0.0; }   // fator de carga
};

// Função da divisão: h(k) = k mod m. O(1)
int funcaoHash(int id, int m);

// Prepara a tabela vazia com m slots e a capacidade máxima do cache
void inicializarHash(TabelaHash& th, int m, int capacidade);

// Insere no cache (início da lista do bucket). Colisão = inserção em bucket já ocupado
// (conta 1). Se cheio, evicta a entrada mais antiga do bucket. O(1) em média
void inserirHash(TabelaHash& th, const Pedido& p);

// Busca no cache; em caso de miss consulta a AVL, cronometrando e acumulando em 'est'
// (buscas, comparações, tempo) e, se achar, insere no cache. nullptr se não existe.
// O ponteiro devolvido vale até a próxima inserção no cache
const Pedido* buscarHash(TabelaHash& th, int id, NoAVL* raizAVL, EstatAVL& est);

// Libera os nós (NÃO libera receitas: pertencem à AVL). Chamar antes de destruirAVL
void destruirHash(TabelaHash& th);

#endif
