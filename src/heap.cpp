#include "heap.h"

using namespace std;

// FUNÇÕES AUXILIARES (visíveis só neste arquivo)
static void trocar(Lote& a, Lote& b) { Lote t = a; a = b; b = t; }

static void siftUp(Heap& h, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (h.v[i].turnoVencimento < h.v[pai].turnoVencimento) {
            trocar(h.v[i], h.v[pai]);
            i = pai;
        } else break;
    }
}

static void siftDown(Heap& h, int i) {
    while (true) {
        int menor = i, esq = 2 * i + 1, dir = 2 * i + 2;
        if (esq < h.tam && h.v[esq].turnoVencimento < h.v[menor].turnoVencimento) menor = esq;
        if (dir < h.tam && h.v[dir].turnoVencimento < h.v[menor].turnoVencimento) menor = dir;
        if (menor == i) break;
        trocar(h.v[i], h.v[menor]);
        i = menor;
    }
}

// INSERÇÃO E REMOÇÃO
void inserirLoteHeap(Heap& h, const Lote& l) {
    if (h.tam == h.cap) {                       // vetor dinâmico: dobra a capacidade
        int novaCap = h.cap == 0 ? 8 : h.cap * 2;
        Lote* nv = new Lote[novaCap];
        for (int i = 0; i < h.tam; i++) nv[i] = h.v[i];
        delete[] h.v;
        h.v = nv;
        h.cap = novaCap;
    }
    h.v[h.tam] = l;
    siftUp(h, h.tam);
    h.tam++;
}

bool removerTopoHeap(Heap& h, Lote& out) {
    if (h.tam == 0) return false;
    out = h.v[0];
    h.tam--;
    h.v[0] = h.v[h.tam];
    if (h.tam > 0) siftDown(h, 0);
    return true;
}

int removerVencidos(Heap& h, int turnoAtual) {
    int k = 0;
    Lote l;
    while (h.tam > 0 && h.v[0].turnoVencimento <= turnoAtual) {
        removerTopoHeap(h, l);
        k++;
    }
    return k;
}

// ESTOQUE (um heap por perecível)
Heap* heapDoIngrediente(Estoque& e, char simbolo) {
    switch (simbolo) {
        case 'n': return &e.heaps[0];
        case 'o': return &e.heaps[1];
        case 'b': return &e.heaps[2];
        default:  return nullptr;
    }
}

int removerVencidosEstoque(Estoque& e, int turnoAtual, int* descartados) {
    int total = 0;
    for (int i = 0; i < 3; i++) {
        int k = removerVencidos(e.heaps[i], turnoAtual);
        if (descartados != nullptr) descartados[i] = k;
        total += k;
    }
    return total;
}

void destruirEstoque(Estoque& e) {
    for (int i = 0; i < 3; i++) {
        delete[] e.heaps[i].v;
        e.heaps[i] = Heap();
    }
    for (int i = 0; i < 4; i++) e.perenes[i] = 0;
}
