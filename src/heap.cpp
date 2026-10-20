#include "heap.h"
#include <utility>

using namespace std;

// FUNÇÕES AUXILIARES (visíveis só neste arquivo)
static void siftUp(vector<Lote>& h, size_t i) {
    while (i > 0) {
        size_t pai = (i - 1) / 2;
        if (h[i].turnoVencimento < h[pai].turnoVencimento) {
            swap(h[i], h[pai]);
            i = pai;
        } else break;
    }
}

static void siftDown(vector<Lote>& h, size_t i) {
    size_t n = h.size();
    while (true) {
        size_t menor = i, esq = 2 * i + 1, dir = 2 * i + 2;
        if (esq < n && h[esq].turnoVencimento < h[menor].turnoVencimento) menor = esq;
        if (dir < n && h[dir].turnoVencimento < h[menor].turnoVencimento) menor = dir;
        if (menor == i) break;
        swap(h[i], h[menor]);
        i = menor;
    }
}

// INSERÇÃO E REMOÇÃO
void inserirLoteHeap(vector<Lote>& h, const Lote& l) {
    h.push_back(l);
    siftUp(h, h.size() - 1);
}

bool removerTopoHeap(vector<Lote>& h, Lote& out) {
    if (h.empty()) return false;
    out = h[0];
    h[0] = h.back();
    h.pop_back();
    if (!h.empty()) siftDown(h, 0);
    return true;
}

int removerVencidos(vector<Lote>& h, int turnoAtual, vector<Lote>* removidos) {
    int k = 0;
    Lote l;
    while (!h.empty() && h[0].turnoVencimento <= turnoAtual) {
        removerTopoHeap(h, l);
        if (removidos != nullptr) removidos->push_back(l);
        k++;
    }
    return k;
}

// ESTOQUE (um heap por ingrediente)
vector<Lote>& heapDoIngrediente(Estoque& e, const string& nome) {
    for (size_t i = 0; i < e.nomes.size(); i++)
        if (e.nomes[i] == nome) return e.heaps[i];
    e.nomes.push_back(nome);
    e.heaps.emplace_back();
    return e.heaps.back();
}

int removerVencidosEstoque(Estoque& e, int turnoAtual) {
    int total = 0;
    for (auto& h : e.heaps) total += removerVencidos(h, turnoAtual);
    return total;
}
