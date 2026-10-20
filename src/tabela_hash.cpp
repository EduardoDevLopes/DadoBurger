#include "tabela_hash.h"

using namespace std;

// FUNÇÃO DE HASH (método da divisão: h(k) = k mod m)
static int funcaoHash(int id, int m) { return ((id % m) + m) % m; }

// EVICÇÃO
// Remove a entrada mais antiga do bucket (cauda, pois a inserção é no início).
// Se o bucket estiver vazio, usa o primeiro bucket não vazio a partir dele.
static void evictar(TabelaHash& th, int idx) {
    for (int k = 0; k < th.m; k++) {
        int i = (idx + k) % th.m;
        NoHash* cur = th.tab[(size_t)i];
        if (cur == nullptr) continue;
        NoHash* ant = nullptr;
        while (cur->prox != nullptr) { ant = cur; cur = cur->prox; }
        if (ant == nullptr) th.tab[(size_t)i] = nullptr;
        else ant->prox = nullptr;
        delete cur;   // só o nó: a receita é da AVL
        th.n--;
        th.evicoes++;
        return;
    }
}

// INICIALIZAÇÃO, INSERÇÃO E BUSCA
void inicializarHash(TabelaHash& th, int m, int capacidade) {
    th.tab.assign((size_t)m, nullptr);
    th.m = m;
    th.n = 0;
    th.capacidade = capacidade;
    th.hits = th.misses = th.colisoes = th.evicoes = 0;
}

void inserirHash(TabelaHash& th, const Pedido& p) {
    int i = funcaoHash(p.id, th.m);
    for (NoHash* a = th.tab[(size_t)i]; a != nullptr; a = a->prox)
        if (a->p.id == p.id) return;                 // já está no cache
    if (th.n >= th.capacidade) evictar(th, i);
    if (th.tab[(size_t)i] != nullptr) th.colisoes++; // bucket já ocupado
    th.tab[(size_t)i] = new NoHash{p, th.tab[(size_t)i]};
    th.n++;
}

const Pedido* buscarHash(TabelaHash& th, int id, NoAVL* raizAVL, int& comp) {
    int i = funcaoHash(id, th.m);
    for (NoHash* a = th.tab[(size_t)i]; a != nullptr; a = a->prox) {
        if (a->p.id == id) { th.hits++; return &a->p; }
    }
    th.misses++;
    NoAVL* r = buscarAVL(raizAVL, id, comp);   // miss: consulta o índice primário
    if (r == nullptr) return nullptr;
    inserirHash(th, r->p);
    return &r->p;
}

// DESTRUIÇÃO
void destruirHash(TabelaHash& th) {
    for (auto& cab : th.tab) {
        while (cab != nullptr) {
            NoHash* prox = cab->prox;
            delete cab;
            cab = prox;
        }
    }
    th.n = 0;
}
