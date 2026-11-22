// TESTES DE UNIDADE - compilar com: make test
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "avl.h"
#include "constants.h"
#include "fila.h"
#include "hash.h"
#include "heap.h"
#include "historico.h"
#include "jogo.h"
#include "lista.h"
#include "ordenacao.h"
#include "partida.h"
#include "pilha.h"

using namespace std;

static int falhas = 0, total = 0;
#define CHECK(c) do { total++; if (!(c)) { falhas++; printf("FALHOU %s:%d  %s\n", __FILE__, __LINE__, #c); } } while (0)

static NoIng* receita(const char* r) {
    NoIng* ini = nullptr;
    for (; *r; r++) inserirIngredienteFim(ini, *r);
    return ini;
}

static bool avlValida(const NoAVL* n, int& h) {
    if (!n) { h = 0; return true; }
    int he, hd;
    if (!avlValida(n->esq, he) || !avlValida(n->dir, hd)) return false;
    if (he - hd > 1 || hd - he > 1) return false;
    h = 1 + (he > hd ? he : hd);
    int te = n->esq ? n->esq->tam : 0, td = n->dir ? n->dir->tam : 0;
    if (n->altura != h || n->tam != 1 + te + td) return false;
    if (n->esq && n->esq->p.id >= n->p.id) return false;
    if (n->dir && n->dir->p.id <= n->p.id) return false;
    return true;
}

static void testarListaEPilha() {
    NoIng* rec = receita("zkmp");
    Pilha chapa;
    for (char s : {'z', 'k', 'm'}) pushIngrediente(chapa, s);
    CHECK(!verificarPedido(chapa, rec));
    pushIngrediente(chapa, 'z');
    CHECK(!verificarPedido(chapa, rec));
    char removido = '\0';
    CHECK(popIngrediente(chapa, &removido) && removido == 'z');
    pushIngrediente(chapa, 'p');
    CHECK(verificarPedido(chapa, rec) && chapa.tam == 4);       // verificação não destrói a pilha
    char buf[8];
    CHECK(copiarPilha(chapa, buf, 8) == 4 && buf[0] == 'z' && buf[3] == 'p' && topoIngrediente(chapa) == 'p');
    destruirPilha(chapa);
    destruirLista(rec);
}

static void testarFila() {
    Fila f;
    for (int i = 1; i <= 3; i++) enfileirarCliente(f, Cliente{i, 0, 2});
    CHECK(reduzirPacienciaFrente(f) == 1);                       // só o da frente perde paciência
    CHECK(f.ini->prox->c.paciencia == 2 && f.fim->c.paciencia == 2);
    CHECK(reduzirPacienciaFrente(f) == 0);
    Cliente c;
    CHECK(desenfileirarCliente(f, c) && c.id == 1 && frenteFila(f)->paciencia == 2);
    CHECK(desenfileirarCliente(f, c) && desenfileirarCliente(f, c) && !desenfileirarCliente(f, c) && f.fim == nullptr);
    CHECK(reduzirPacienciaFrente(f) == -1);
}

static void testarHeap() {
    Estoque e;
    Heap& h = e.heaps[0];
    for (int t : {9, 3, 7, 1, 5}) inserirLoteHeap(h, Lote{'n', t});
    CHECK(h.v[0].turnoVencimento == 1);
    CHECK(removerVencidos(h, 5) == 3 && h.tam == 2 && h.v[0].turnoVencimento == 7);
    Lote l; int ant = -1; bool ok = true;
    while (removerTopoHeap(h, l)) { if (l.turnoVencimento < ant) ok = false; ant = l.turnoVencimento; }
    CHECK(ok && !removerTopoHeap(h, l));
    CHECK(heapDoIngrediente(e, 'o') == &e.heaps[1] && heapDoIngrediente(e, 'k') == nullptr);
    destruirEstoque(e);
}

static void testarAVL() {
    NoAVL* r = nullptr; int rot = 0;
    for (int i = 1; i <= 3; i++) r = inserirAVL(r, Pedido{i, receita("nz")}, rot);
    CHECK(rot == 1 && alturaAVL(r) == 2);                        // RR: 1 rotação; raiz sozinha = 1
    destruirAVL(r); rot = 0;
    r = inserirAVL(r, Pedido{3, receita("nz")}, rot);
    r = inserirAVL(r, Pedido{1, receita("nz")}, rot);
    r = inserirAVL(r, Pedido{2, receita("nz")}, rot);
    CHECK(rot == 2 && r->p.id == 2);                             // LR: dupla = 2 rotações
    r = inserirAVL(r, Pedido{2, receita("kz")}, rot);
    CHECK(contarNosAVL(r) == 3);                                 // duplicado ignorado
    int comp = 0;
    CHECK(buscarAVL(r, 2, comp) && comp == 1);
    comp = 0; CHECK(buscarAVL(r, 99, comp) == nullptr && comp == 2);
    destruirAVL(r);
    CHECK(alturaAVL(nullptr) == 0);
    for (int modo = 0; modo < 2; modo++) {                       // crescente e pseudo-aleatória
        r = nullptr; rot = 0; unsigned x = 12345;
        const int N = 20000;
        for (int i = 1; i <= N; i++) {
            int id = modo == 0 ? i : (int)((x = x * 1103515245u + 12345u) % 1000003u);
            r = inserirAVL(r, Pedido{id, receita("pz")}, rot);
        }
        int h; CHECK(avlValida(r, h));
        CHECK(h <= 1.44 * log2((double)contarNosAVL(r) + 2));
        if (modo == 0) {
            CHECK(rot == N - 15);                                // n - ceil(log2(n+1)) rotações
            CHECK(selecionarAVL(r, 0)->p.id == 1 && selecionarAVL(r, N - 1)->p.id == N && selecionarAVL(r, N) == nullptr);
        }
        destruirAVL(r);
    }
}

static void testarHash() {
    NoAVL* raiz = nullptr; int rot = 0;
    for (int i = 1; i <= 1000; i++) raiz = inserirAVL(raiz, Pedido{i, receita("pz")}, rot);
    EstatAVL est;
    TabelaHash th;
    inicializarHash(th, 211, 50);
    CHECK(buscarHash(th, 42, raiz, est) != nullptr && th.misses == 1 && est.buscas == 1 && est.totalComp > 0);
    CHECK(buscarHash(th, 42, raiz, est) != nullptr && th.hits == 1 && est.buscas == 1);   // hit não toca a AVL
    CHECK(buscarHash(th, 5000, raiz, est) == nullptr);
    for (int i = 1; i <= 200; i++) buscarHash(th, i, raiz, est);
    CHECK(th.n <= 50 && th.evicoes > 0);
    destruirHash(th);
    TabelaHash t2; inicializarHash(t2, 7, 100);                  // colisão: 15 e 22 caem no slot 1
    inserirHash(t2, Pedido{15, nullptr}); inserirHash(t2, Pedido{22, nullptr}); inserirHash(t2, Pedido{3, nullptr});
    CHECK(t2.n == 3 && t2.colisoes == 1 && funcaoHash(-1, 7) == 6);
    destruirHash(t2);
    destruirAVL(raiz);
}

static void testarOrdenacao() {
    ListaContigua l; inicializarLista(l);
    const char* nm[] = {"bruno", "Ana", "ana", "Carlos", "Ana"};
    int pt[] = {5, 7, 9, 5, 7};
    for (int i = 0; i < 5; i++) { Entrada e; strcpy(e.nome, nm[i]); e.pontos = pt[i]; acrescentar(l, e); }
    Entrada* o = nullptr; medirOrdenacao(l, maiorPontuacao, &o);
    CHECK(o[0].pontos == 9 && o[4].pontos == 5 && strcmp(o[4].nome, "Carlos") == 0);
    CHECK(strcmp(l.v[0].nome, "bruno") == 0);                    // original intacto
    delete[] o;
    medirOrdenacao(l, ordemAlfabetica, &o);
    CHECK(strcmp(o[0].nome, "ana") == 0 && o[0].pontos == 9 && strcmp(o[3].nome, "bruno") == 0);
    delete[] o;
    for (int i = 0; i < 5000; i++) { Entrada e; snprintf(e.nome, 21, "N%d", rand() % 900); e.pontos = rand() % 41; acrescentar(l, e); }
    Entrada* a = copiarVetor(l); Entrada* b = copiarVetor(l);
    CriterioEntrada crit[2] = {maiorPontuacao, ordemAlfabetica};
    for (int c = 0; c < 2; c++) {
        ordenarHistorico(a, l.tam, crit[c]); heapSortHistorico(b, l.tam, crit[c]);
        bool igual = true;
        for (int i = 0; i < l.tam; i++) if (a[i].pontos != b[i].pontos || strcmp(a[i].nome, b[i].nome)) igual = false;
        CHECK(igual);
        for (int i = 1; i < l.tam; i++) if (crit[c](a[i], a[i - 1])) igual = false;
        CHECK(igual);                                            // nenhum par fora de ordem
    }
    delete[] a; delete[] b; destruirLista(l);
}

static void testarHistoricoArquivo() {
    const char* f = "/tmp/hist_teste.txt";
    remove(f);
    ListaContigua l; inicializarLista(l);
    CHECK(carregarHistorico(f, l) == 0);                         // inexistente => vazio
    Entrada e; strcpy(e.nome, "Maria S."); e.pontos = 3;
    CHECK(anexarHistorico(f, e)); strcpy(e.nome, "Joao"); e.pontos = 10; CHECK(anexarHistorico(f, e));
    CHECK(carregarHistorico(f, l) == 2 && l.v[1].pontos == 10 && strcmp(l.v[0].nome, "Maria S.") == 0);
    destruirLista(l); remove(f);
}

// Regras da partida (cenário do Apêndice B)
static void testarPartida() {
    Jogo j; j.gerador.seed(1);
    inicializarHash(j.cache, TAMANHO_HASH, CAPACIDADE_CACHE);
    inicializarLista(j.historico);
    int rot = 0;
    j.indice = inserirAVL(j.indice, Pedido{1001, receita("nkmpz")}, rot);
    iniciarPartida(j);
    Partida& p = j.partida;
    CHECK(j.cache.misses == 1 && j.estatAVL.buscas == 1 && j.estatAVL.totalComp == 1);
    CHECK(!acaoAdicionar(j, 'n') && p.turno == 1);               // sem carne: não consome turno
    CHECK(acaoPreparar(j, 'n') && p.turno == 2);
    CHECK(acaoAdicionar(j, 'n'));
    for (const char* s = "kmpz"; *s; s++) { if (*s == 'z') CHECK(p.pontuacao == 0); CHECK(acaoAdicionar(j, *s)); }
    CHECK(p.pontuacao == 1 && p.balcao.tam == NUM_CLIENTES - 1);
    CHECK(j.cache.hits == 1);                                    // 2º cliente: mesmo código => HIT
    CHECK(frenteFila(p.balcao)->paciencia == PACIENCIA_INICIAL); // paciência cheia ao chegar na frente
    int t0 = p.turno;
    CHECK(acaoPreparar(j, 'n'));
    CHECK(quantidadeEstoque(p, 'n') == 1);
    for (int i = 0; i < VALIDADE_CARNE - 1; i++) CHECK(acaoPreparar(j, 't'));
    CHECK(p.turno == t0 + VALIDADE_CARNE);
    CHECK(quantidadeEstoque(p, 'n') == 0);                       // perecível descartada no início do turno
    CHECK(quantidadeEstoque(p, 't') == VALIDADE_CARNE - 1);      // perene permanece
    CHECK(acaoAdicionar(j, 'z'));                                // fecha (errado)
    CHECK(!acaoAdicionar(j, 'k'));                               // nada sobre o pão de cima
    CHECK(acaoRemoverTopo(j) && p.chapa.tam == 0);
    CHECK(!acaoRemoverTopo(j));
    CHECK(!acaoPreparar(j, 'k'));                                // ketchup não tem preparo
    int guard = 0;
    while (p.estado == EM_ANDAMENTO && guard++ < 100) acaoPreparar(j, 'c');
    CHECK(p.estado == DERROTA && p.pontuacao == 1);
    destruirHash(j.cache); reiniciarPartida(j); destruirAVL(j.indice);
}

int main() {
    testarListaEPilha(); testarFila(); testarHeap(); testarAVL(); testarHash();
    testarOrdenacao(); testarHistoricoArquivo(); testarPartida();
    cout << total << " verificacoes, " << falhas << " falhas\n";
    if (falhas == 0) cout << "Todos os testes passaram.\n";
    return falhas ? 1 : 0;
}
