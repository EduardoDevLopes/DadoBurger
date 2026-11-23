#include "partida.h"
#include "constants.h"
#include <iostream>

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

static void inicializarFilaClientes(Jogo& j) {
    
    for (int i = 1; i <= NUM_CLIENTES; i++)
    {
        Cliente cliente;
        cliente.id = i;
        if (j.indice->tam > 0) cliente.idPedido = sortearPedido(j.gerador, 1, j.indice->tam);
        else {
            cliente.idPedido = 0;
            cerr << "Aviso! Número de pedidos encontrados: 0.";
        }
        cliente.paciencia = PACIENCIA_INICIAL;

        enfileirarCliente(j.partida.balcao, cliente);
    }
}

// PARTIDA
void iniciarPartida(Jogo& j) {

    // Inicializa a fila de clientes
    inicializarFilaClientes(j);

    // Define cliente e pedido atual
    Cliente* clienteAtual = frenteFila(j.partida.balcao);
    j.partida.clienteAtual = clienteAtual->id;
    j.partida.pedido = buscarHash(j.cache, clienteAtual->idPedido, j.indice, j.estatAVL);
}

// Início de cada turno, ANTES da ação: descarta vencidos no topo de cada heap
static void inicioDeTurno(Jogo& j) {
}

// Fim de uma ação válida: pedido concluído? paciência? próximo turno
static void fimDeAcao(Jogo& j, bool concluiu) { 
}

bool acaoPreparar(Jogo& j, char s) {

    // Perenes: queijo suíço, queijo cheddar, cebola, tomate. 
    // Cada ação de preparo produz uma unidade no estoque. Uma vez preparados, aguardam indefinidamente.
    int indiceP = indicePerene(s);
    if (indiceP != -1) 
    {
        j.partida.estoque.perenes[indiceP]++;
        return true;
    }

    // Perecíveis: carne, ovo frito, bacon. 
    // Uma vez preparados, devem ser descartados após um número de turnos definido
    if (ehPerecivel(s)) 
    {
        Lote lote;
        lote.ingrediente = s;
        lote.turnoVencimento = validadeDe(s);

        inserirLoteHeap(*heapDoIngrediente(j.partida.estoque, s), lote);

        return true;
    }

    return false;
}

bool acaoAdicionar(Jogo& j, char s) {

    // verificar se é possível adicionar o ingrediente
    if (!ingredienteValido(s)) return false;

    int indiceP = indicePerene(s);
    if (indiceP != -1) {
        if (j.partida.estoque.perenes[indiceP] < 1) return false; // sem ingrediente no estoque

        j.partida.estoque.perenes[indiceP]--;   // ingrediente é utilizado
    }
    else if (ehPerecivel(s)) {
        Lote lote;
        if (!removerTopoHeap(*heapDoIngrediente(j.partida.estoque, s), lote)) return false;
    }

    pushIngrediente(j.partida.chapa, s);

    return true;
}

// REMOVER TOPO: desempilha e DESCARTA (não volta ao estoque). Consome 1 turno.
bool acaoRemoverTopo(Jogo& j) {
    Partida& p = j.partida;
    p.msg[0] = '\0';
    char r;
    if (!popIngrediente(p.chapa, &r)) { snprintf(p.msg, sizeof p.msg, "O prato esta vazio. "); return false; }
    snprintf(p.msg, sizeof p.msg, "Descartou %s do topo. ", nomeIngrediente(r));
    fimDeAcao(j, false);
    return true;
}


void acaoSair(Jogo& j) { j.partida.estado = SAIDA_VOLUNTARIA; }
