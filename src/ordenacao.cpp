#include "ordenacao.h"
#include "timer.hpp"

using namespace std;

// CRITÉRIOS DE ORDENAÇÃO
static int cmpNome(const char* a, const char* b) {
    for (;; a++, b++) {
        int x = (unsigned char)*a, y = (unsigned char)*b;
        if (x >= 'A' && x <= 'Z') x += 32;
        if (y >= 'A' && y <= 'Z') y += 32;
        if (x != y) return x < y ? -1 : 1;
        if (x == 0) return 0;
    }
}

bool maiorPontuacao(const Entrada& a, const Entrada& b) {
    if (a.pontos != b.pontos) return a.pontos > b.pontos;
    return cmpNome(a.nome, b.nome) < 0;
}

bool ordemAlfabetica(const Entrada& a, const Entrada& b) {
    int r = cmpNome(a.nome, b.nome);
    if (r != 0) return r < 0;
    return a.pontos > b.pontos;
}

// MERGE SORT
static void msort(Entrada* v, Entrada* aux, int ini, int fim, CriterioEntrada antes) {
    if (fim - ini < 2) return;
    int meio = ini + (fim - ini) / 2;
    msort(v, aux, ini, meio, antes);
    msort(v, aux, meio, fim, antes);
    int i = ini, j = meio, k = ini;
    while (i < meio && j < fim) aux[k++] = antes(v[j], v[i]) ? v[j++] : v[i++];
    while (i < meio) aux[k++] = v[i++];
    while (j < fim) aux[k++] = v[j++];
    for (k = ini; k < fim; k++) v[k] = aux[k];
}

void ordenarHistorico(Entrada* v, int n, CriterioEntrada antes) {
    if (n < 2) return;
    Entrada* aux = new Entrada[n];
    msort(v, aux, 0, n, antes);
    delete[] aux;
}

// HEAP SORT (do esqueleto, agora sobre vetor próprio)
static void heapifyEntrada(Entrada* v, int n, int i, CriterioEntrada antes) {
    while (true) {
        int ultimo = i, esq = 2 * i + 1, dir = 2 * i + 2;
        if (esq < n && antes(v[ultimo], v[esq])) ultimo = esq;   // filho que vem "depois" sobe
        if (dir < n && antes(v[ultimo], v[dir])) ultimo = dir;
        if (ultimo == i) break;
        Entrada t = v[i]; v[i] = v[ultimo]; v[ultimo] = t;
        i = ultimo;
    }
}

void heapSortHistorico(Entrada* v, int n, CriterioEntrada antes) {
    if (n < 2) return;
    for (int i = n / 2 - 1; i >= 0; i--) heapifyEntrada(v, n, i, antes);   // build-heap O(n)
    for (int i = n - 1; i > 0; i--) {                                      // extrações O(n log n)
        Entrada t = v[0]; v[0] = v[i]; v[i] = t;
        heapifyEntrada(v, i, 0, antes);
    }
}

// MEDIÇÃO DE DESEMPENHO
double medirOrdenacao(const ListaContigua& hist, CriterioEntrada antes, Entrada** saida) {
    Entrada* copia = copiarVetor(hist);          // fora do cronômetro
    Timer t;
    timer_iniciar(&t);
    ordenarHistorico(copia, hist.tam, antes);
    double s = timer_parar(&t);
    if (saida != nullptr) *saida = copia; else delete[] copia;
    return s;
}
