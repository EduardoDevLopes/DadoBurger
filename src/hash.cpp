#include "hash.h"
#include "timer.hpp"

using namespace std;

// FUNÇÃO DE HASH (método da divisão: h(k) = k mod m)
int funcaoHash(int id, int m) { return ((id % m) + m) % m; }

// EVICÇÃO
// Remove a entrada mais antiga do bucket (cauda, pois a inserção é no início).
// Se o bucket estiver vazio, usa o primeiro bucket não vazio a partir dele.
static void evictar(TabelaHash& th, int idx) {
    for (int k = 0; k < th.m; k++) {
        int i = (idx + k) % th.m;
        NoHash* cur = th.tab[i];
        if (cur == nullptr) continue;
        NoHash* ant = nullptr;
        while (cur->prox != nullptr) { ant = cur; cur = cur->prox; }
        if (ant == nullptr) th.tab[i] = nullptr;
        else ant->prox = nullptr;
        delete cur;   // só o nó: a receita é da AVL
        th.n--;
        th.evicoes++;
        return;
    }
}

// INICIALIZAÇÃO, INSERÇÃO E BUSCA
void inicializarHash(TabelaHash& th, int m, int capacidade) {
    th.tab = new NoHash*[m];
    for (int i = 0; i < m; i++) th.tab[i] = nullptr;
    th.m = m;
    th.n = 0;
    th.capacidade = capacidade;
    th.hits = th.misses = th.colisoes = th.evicoes = 0;
}

void inserirHash(TabelaHash& th, const Pedido& p) {
    int i = funcaoHash(p.id, th.m);
    for (NoHash* a = th.tab[i]; a != nullptr; a = a->prox)
        if (a->p.id == p.id) return;                 // já está no cache
    if (th.n >= th.capacidade) evictar(th, i);
    if (th.tab[i] != nullptr) th.colisoes++;         // bucket já ocupado
    th.tab[i] = new NoHash{p, th.tab[i]};
    th.n++;
}

const Pedido* buscarHash(TabelaHash& th, int id, NoAVL* raizAVL, EstatAVL& est) {
    int i = funcaoHash(id, th.m);
    for (NoHash* a = th.tab[i]; a != nullptr; a = a->prox) {
        if (a->p.id == id) { th.hits++; return &a->p; }
    }
    th.misses++;
    int comp = 0;
    Timer t;
    timer_iniciar(&t);
    NoAVL* r = buscarAVL(raizAVL, id, comp);   // miss: consulta o índice primário
    est.tempoBuscas += timer_parar(&t);
    est.buscas++;
    est.totalComp += comp;
    if (r == nullptr) return nullptr;
    inserirHash(th, r->p);
    return &r->p;
}

// DESTRUIÇÃO
void destruirHash(TabelaHash& th) {
    for (int i = 0; i < th.m; i++) {
        while (th.tab[i] != nullptr) {
            NoHash* prox = th.tab[i]->prox;
            delete th.tab[i];
            th.tab[i] = prox;
        }
    }
    delete[] th.tab;
    th.tab = nullptr;
    th.m = 0;
    th.n = 0;
}
