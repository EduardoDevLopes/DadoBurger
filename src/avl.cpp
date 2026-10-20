#include "avl.h"
#include <algorithm>

using namespace std;

// FUNÇÕES AUXILIARES DE ALTURA E BALANCEAMENTO
static int alturaNo(const NoAVL* n) { return n == nullptr ? -1 : n->altura; }
static void atualizarAltura(NoAVL* n) { n->altura = 1 + max(alturaNo(n->esq), alturaNo(n->dir)); }
static int fatorBalanco(const NoAVL* n) { return n == nullptr ? 0 : alturaNo(n->esq) - alturaNo(n->dir); }

// ROTAÇÕES (cada chamada incrementa o contador)
static NoAVL* rotDireita(NoAVL* y, int& rot) {
    NoAVL* x = y->esq;
    y->esq = x->dir;
    x->dir = y;
    atualizarAltura(y);   // y agora está abaixo: atualiza primeiro
    atualizarAltura(x);
    rot++;
    return x;
}

static NoAVL* rotEsquerda(NoAVL* x, int& rot) {
    NoAVL* y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    atualizarAltura(x);
    atualizarAltura(y);
    rot++;
    return y;
}

// Casos: LL, LR (fb > 1) e RR, RL (fb < -1)
static NoAVL* rebalancear(NoAVL* no, int& rot) {
    atualizarAltura(no);
    int fb = fatorBalanco(no);
    if (fb > 1) {
        if (fatorBalanco(no->esq) < 0) no->esq = rotEsquerda(no->esq, rot);   // LR
        return rotDireita(no, rot);
    }
    if (fb < -1) {
        if (fatorBalanco(no->dir) > 0) no->dir = rotDireita(no->dir, rot);   // RL
        return rotEsquerda(no, rot);
    }
    return no;
}

// INSERÇÃO E BUSCA
NoAVL* inserirAVL(NoAVL* no, Pedido p, int& rot) {
    if (no == nullptr) return new NoAVL{p, 0, nullptr, nullptr};
    if (p.id < no->p.id) no->esq = inserirAVL(no->esq, p, rot);
    else if (p.id > no->p.id) no->dir = inserirAVL(no->dir, p, rot);
    else {
        destruirLista(p.receita);   // duplicado: não deixa a receita vazar
        return no;
    }
    return rebalancear(no, rot);
}

NoAVL* buscarAVL(NoAVL* r, int id, int& comp) {
    while (r != nullptr) {
        comp++;
        if (id == r->p.id) return r;
        r = (id < r->p.id) ? r->esq : r->dir;
    }
    return nullptr;
}

// CONSULTAS E DESTRUIÇÃO
int alturaAVL(const NoAVL* r) { return alturaNo(r); }

int contarNosAVL(const NoAVL* r) {
    return r == nullptr ? 0 : 1 + contarNosAVL(r->esq) + contarNosAVL(r->dir);
}

void destruirAVL(NoAVL*& r) {
    if (r == nullptr) return;
    destruirAVL(r->esq);
    destruirAVL(r->dir);
    destruirLista(r->p.receita);
    delete r;
    r = nullptr;
}
