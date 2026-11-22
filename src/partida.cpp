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

static void inicializaFilaClientes(Jogo& j) {
    
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
    inicializaFilaClientes(j);

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
    return true;
}

bool acaoAdicionar(Jogo& j, char s) {
    return true;
}

bool acaoRemoverTopo(Jogo& j) {
    return true;
}

void acaoSair(Jogo& j) { j.partida.estado = SAIDA_VOLUNTARIA; }
