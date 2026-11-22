#include "partida.h"
#include "constants.h"
#include <cstdio>
#include <cstring>

using namespace std;

// INGREDIENTES
static const char SIMBOLOS[] = "zkmpasqctnob";
static const char* NOMES[] = {"pao de cima", "ketchup", "mostarda", "picles", "alface",
    "queijo suico", "queijo cheddar", "cebola", "tomate", "carne", "ovo frito", "bacon"};

static int pos(char s) {
    for (int i = 0; SIMBOLOS[i]; i++) if (SIMBOLOS[i] == s) return i;
    return -1;
}
const char* nomeIngrediente(char s) { int i = pos(s); return i < 0 ? nullptr : NOMES[i]; }
bool ingredienteValido(char s) { return pos(s) >= 0; }
static int indicePerene(char s) { return s == 's' ? 0 : s == 'q' ? 1 : s == 'c' ? 2 : s == 't' ? 3 : -1; }
bool ehPerecivel(char s) { return s == 'n' || s == 'o' || s == 'b'; }
bool requerPreparo(char s) { return ehPerecivel(s) || indicePerene(s) >= 0; }
int validadeDe(char s) { return s == 'n' ? VALIDADE_CARNE : s == 'o' ? VALIDADE_OVO : VALIDADE_BACON; }

int quantidadeEstoque(const Partida& p, char s) {
}

// SORTEIO + CACHE + AVL
// Sorteia uma POSIÇÃO k entre os n pedidos existentes e pega o k-ésimo id na AVL (O(log n));
// depois consulta o cache (hit) ou a AVL (miss, cronometrada e contada em estatAVL).
static void sortearEBuscarPedido(Jogo& j) {
}

// PARTIDA
void iniciarPartida(Jogo& j) {
}

// Início de cada turno, ANTES da ação: descarta vencidos no topo de cada heap
static void inicioDeTurno(Jogo& j) {
}

// Fim de uma ação válida: pedido concluído? paciência? próximo turno
static void fimDeAcao(Jogo& j, bool concluiu) { 
}

bool acaoPreparar(Jogo& j, char s) {
    return true;
}

bool acaoAdicionar(Jogo& j, char s) {
    return true;
}

bool acaoRemoverTopo(Jogo& j) {
    return true;
}

void acaoSair(Jogo& j) { j.partida.estado = SAIDA_VOLUNTARIA; }
