#ifndef AVL_H
#define AVL_H
#include "pedido.h"

// ÁRVORE AVL - índice primário de pedidos (chave: id), instrumentada
struct NoAVL {
    Pedido p;
    int altura;    // enunciado (§5.1): árvore vazia = 0, só a raiz = 1 (folha = 1)
    int tam;       // nº de nós da subárvore (permite sortear o k-ésimo pedido em O(log n))
    NoAVL* esq;
    NoAVL* dir;
};

// Métricas exigidas no relatório (seção "AVL - carregamento e buscas")
struct EstatAVL {
    int nos = 0;
    int altura = 0;
    int rotacoes = 0;
    double tempoCarga = 0.0;    // segundos
    long totalComp = 0;         // comparações acumuladas nas buscas (zeradas a cada partida)
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

// Devolve o nó de posição k (0-based) na ordem crescente de ids. O(log n). Usado no
// sorteio: escolher uma POSIÇÃO entre os n pedidos existentes funciona mesmo que os
// códigos não sejam 1..n (o esqueleto sorteava de 1 a n e assumia códigos contíguos)
NoAVL* selecionarAVL(NoAVL* r, int k);

int alturaAVL(const NoAVL* r);
int contarNosAVL(const NoAVL* r);   // O(1): usa o campo tam

// Libera a árvore inteira, incluindo as receitas (pós-ordem)
void destruirAVL(NoAVL*& r);

#endif
