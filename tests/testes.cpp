// TESTES DE UNIDADE - compilar com: make test
#include <cassert>
#include <cmath>
#include <iostream>
#include "avl.h"
#include "fila.h"
#include "heap.h"
#include "historico.h"
#include "lista.h"
#include "pilha.h"
#include "tabela_hash.h"

using namespace std;

static void testarListaEPilha() {
    NoIng* rec = nullptr;
    for (const char* s : {"pao", "carne", "queijo", "pao"}) inserirIngredienteFim(rec, s);
    Pilha chapa;
    for (const char* s : {"pao", "carne", "queijo"}) pushIngrediente(chapa, s);
    assert(!verificarPedido(chapa, rec));
    pushIngrediente(chapa, "alface");
    string r;
    assert(popIngrediente(chapa, &r) && r == "alface");
    pushIngrediente(chapa, "pao");
    assert(verificarPedido(chapa, rec));
    destruirPilha(chapa);
    destruirLista(rec);
}

static void testarFila() {
    Fila f;
    for (int i = 1; i <= 3; i++) enfileirarCliente(f, Cliente{i, i, i});
    assert(atualizarPaciencia(f) == 1 && f.tam == 2);    // cliente 1 desiste
    Cliente c;
    assert(desenfileirarCliente(f, c) && c.id == 2);
    assert(atualizarPaciencia(f) == 0 && f.tam == 1);
    assert(atualizarPaciencia(f) == 1 && f.tam == 0 && f.fim == nullptr);
    destruirFila(f);
}

static void testarHeap() {
    vector<Lote> h;
    for (int t : {9, 3, 7, 1, 5}) inserirLoteHeap(h, Lote{"alface", 1, t});
    assert(h[0].turnoVencimento == 1);
    assert(removerVencidos(h, 5) == 3 && h.size() == 2 && h[0].turnoVencimento == 7);
}

static void testarAVLEHash() {
    NoAVL* raiz = nullptr;
    int rot = 0;
    const int N = 1000;
    for (int i = 1; i <= N; i++) raiz = inserirAVL(raiz, Pedido{i, "p", nullptr}, rot);
    assert(contarNosAVL(raiz) == N);
    assert(alturaAVL(raiz) <= (int)(1.44 * log2((double)N + 2)));   // limite teórico
    int comp = 0;
    assert(buscarAVL(raiz, 777, comp) != nullptr && comp <= alturaAVL(raiz) + 1);
    assert(buscarAVL(raiz, 5000, comp) == nullptr);

    TabelaHash th;
    inicializarHash(th, 211, 50);
    int c2 = 0;
    assert(buscarHash(th, 42, raiz, c2) != nullptr && th.misses == 1);
    assert(buscarHash(th, 42, raiz, c2) != nullptr && th.hits == 1);
    for (int i = 1; i <= 200; i++) buscarHash(th, i, raiz, c2);
    assert(th.n <= 50 && th.evicoes > 0);
    destruirHash(th);
    destruirAVL(raiz);
}

static void testarOrdenacao() {
    vector<Partida> hist;
    for (int i = 0; i < 500; i++) hist.push_back(Partida{i, (i * 37) % 101, (i * 13) % 59});
    ordenarHistorico(hist);
    for (size_t i = 1; i < hist.size(); i++) assert(hist[i - 1].pontuacao >= hist[i].pontuacao);
    ordenarHistorico(hist, menorTempo);
    for (size_t i = 1; i < hist.size(); i++) assert(hist[i - 1].tempoAtendimento <= hist[i].tempoAtendimento);
}

int main() {
    testarListaEPilha();
    testarFila();
    testarHeap();
    testarAVLEHash();
    testarOrdenacao();
    cout << "Todos os testes passaram.\n";
    return 0;
}
