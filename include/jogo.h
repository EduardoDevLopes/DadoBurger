#ifndef JOGO_H
#define JOGO_H
#include <cstdio>
#include <random>
#include <string>
#include "avl.h"
#include "hash.h"
#include "fila.h"
#include "pilha.h"
#include "heap.h"
#include "historico.h"

// ESTADO GLOBAL DO JOGO
// Reúne todas as estruturas de dados da sessão em um único objeto, passado por referência
// aos módulos (sem variáveis globais). O estado de UMA partida fica em Jogo::partida,
// recriado a cada "Novo jogo".

enum EstadoPartida { EM_ANDAMENTO, VITORIA, DERROTA, SAIDA_VOLUNTARIA };

struct Partida {
    Fila balcao;                         // clientes aguardando atendimento
    Pilha chapa;                         // montagem do hambúrguer atual
    Estoque estoque;                     // heaps de perecíveis + contadores dos perenes
    int turno = 1;                       // turno atual (1-based)
    int pontuacao = 0;                   // clientes atendidos
    int clienteAtual = 0;                // 1..NUM_CLIENTES
    const Pedido* pedido = nullptr;      // pedido do cliente da frente
    EstadoPartida estado = EM_ANDAMENTO;
    char msg[200] = "";                  // aviso do último turno (exibido na tela)
};

// Última ordenação do histórico (para o relatório)
struct EstatOrdenacao {
    int acessos = 0;
    int tamanho = 0;
    double tempo = 0.0;
    const char* criterio = "";
};

struct Jogo {
    NoAVL* indice = nullptr;          // AVL com todos os pedidos
    TabelaHash cache;                 // cache de pedidos (hash)
    ListaContigua historico;          // partidas encerradas (lista contígua)
    std::string arqHistorico;         // arquivo do histórico (argv[2])
    Partida partida;                  // partida em andamento
    EstatAVL estatAVL;                // métricas da AVL (carga + buscas da partida)
    EstatOrdenacao estatOrd;          // métricas da ordenação do histórico
    int entradasCarregadas = 0;       // tamanho do histórico logo após a carga
    int numPartida = 0;               // partidas jogadas na sessão
    FILE* log = nullptr;              // medicoes.log

    // mt19937 é uma classe que contem um algoritmo para gerar numeros pseudoaleatórios a partir de uma seed dada
    std::mt19937 gerador;             // gerador para sorteio de pedidos
};

// Carrega pedidos na AVL e o histórico na lista contígua, prepara o cache e abre o log.
// Retorna false se o arquivo de pedidos não abrir (histórico ausente = lista vazia)
bool iniciarJogo(Jogo& j, const std::string& arquivoPedidos, const std::string& arquivoHistorico);

// Zera o estado de UMA partida (fila, chapa, estoque, turno, pontuação), mantendo AVL,
// cache e histórico. Chamar ao escolher "Novo jogo"
void reiniciarPartida(Jogo& j);

// Libera toda a memória do jogo (cache antes da AVL, pois compartilham receitas)
void encerrarJogo(Jogo& j);

#endif
