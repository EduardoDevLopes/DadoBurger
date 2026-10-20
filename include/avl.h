#ifndef AVL_H
#define AVL_H
#include "pedido.h"

// ÁRVORE AVL - índice primário de pedidos (chave: id), instrumentada
struct NoAVL {
    Pedido p;
    int altura;    // folha = 0, nó nulo = -1
    NoAVL* esq;
    NoAVL* dir;
};

// Métricas exigidas no relatório (seção "AVL - carregamento e buscas")
struct EstatAVL {
    int nos = 0;
    int altura = -1;
    int rotacoes = 0;
    double tempoCarga = 0.0;    // segundos
    long totalComp = 0;         // comparações acumuladas nas buscas
    long buscas = 0;
    double tempoBuscas = 0.0;   // segundos
    double mediaComp() const { return buscas > 0 ? (double)totalComp / (double)buscas : 0.0; }
};

// Insere mantendo o balanceamento; 'rot' acumula as rotações
// (rotação simples = 1, dupla = 2). Se o id já existir, a receita recebida é
// liberada (evita vazamento) e nada é inserido. Retorna a nova raiz. O(log n)
NoAVL* inserirAVL(NoAVL* no, Pedido p, int& rot);

// Busca pelo id; 'comp' acumula os nós comparados (1 por nó visitado). O(log n)
NoAVL* buscarAVL(NoAVL* r, int id, int& comp);

int alturaAVL(const NoAVL* r);
int contarNosAVL(const NoAVL* r);

// Libera a árvore inteira, incluindo as receitas (pós-ordem)
void destruirAVL(NoAVL*& r);

#endif
