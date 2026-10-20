#ifndef JOGO_H
#define JOGO_H
#include <string>
#include <vector>
#include "avl.h"
#include "tabela_hash.h"
#include "fila.h"
#include "pilha.h"
#include "heap.h"
#include "historico.h"

// ESTADO GLOBAL DO JOGO
// Reúne todas as estruturas de dados da simulação em um único objeto,
// passado por referência aos módulos (evita variáveis globais).
struct Jogo {
    NoAVL* indice = nullptr;          // AVL com todos os pedidos
    TabelaHash cache;                 // cache de pedidos frequentes
    Fila balcao;                      // clientes aguardando atendimento
    Pilha chapa;                      // montagem do hambúrguer atual
    Estoque estoque;                  // heaps de lotes perecíveis
    std::vector<Partida> historico;   // partidas encerradas
    EstatAVL estatAVL;                // métricas da carga da AVL
    int turno = 0;
    int pontuacao = 0;
};

// Carrega pedidos na AVL e prepara o cache. Retorna false se o arquivo não abrir
bool iniciarJogo(Jogo& j, const std::string& arquivoPedidos);

// Zera o estado de UMA partida (fila, chapa, estoque, turno, pontuação),
// mantendo AVL, cache e histórico. Chamar ao escolher "Novo jogo"
void reiniciarPartida(Jogo& j);

// Libera toda a memória do jogo (cache antes da AVL, pois compartilham receitas)
void encerrarJogo(Jogo& j);

#endif
