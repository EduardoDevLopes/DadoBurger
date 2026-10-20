#include "historico.h"
#include <chrono>
#include <utility>

using namespace std;

// CRITÉRIOS DE ORDENAÇÃO
bool maiorPontuacao(const Partida& a, const Partida& b) { return a.pontuacao > b.pontuacao; }
bool menorTempo(const Partida& a, const Partida& b) { return a.tempoAtendimento < b.tempoAtendimento; }

// HEAP SORT
static void heapifyPartida(vector<Partida>& v, size_t n, size_t i, CriterioPartida antes) {
    while (true) {
        size_t ultimo = i, esq = 2 * i + 1, dir = 2 * i + 2;
        if (esq < n && antes(v[ultimo], v[esq])) ultimo = esq;   // filho que vem "depois" sobe
        if (dir < n && antes(v[ultimo], v[dir])) ultimo = dir;
        if (ultimo == i) break;
        swap(v[i], v[ultimo]);
        i = ultimo;
    }
}

void ordenarHistorico(vector<Partida>& hist, CriterioPartida antes) {
    size_t n = hist.size();
    if (n < 2) return;
    for (size_t i = n / 2; i-- > 0;) heapifyPartida(hist, n, i, antes);   // build-heap O(n)
    for (size_t i = n - 1; i > 0; i--) {                                  // extrações O(n log n)
        swap(hist[0], hist[i]);
        heapifyPartida(hist, i, 0, antes);
    }
}

// MEDIÇÃO DE DESEMPENHO
double medirOrdenacao(const vector<Partida>& hist, CriterioPartida antes) {
    vector<Partida> copia = hist;
    auto t0 = chrono::steady_clock::now();
    ordenarHistorico(copia, antes);
    auto t1 = chrono::steady_clock::now();
    return chrono::duration<double>(t1 - t0).count();
}
