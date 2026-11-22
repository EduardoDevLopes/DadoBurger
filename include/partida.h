#ifndef PARTIDA_H
#define PARTIDA_H
#include "jogo.h"

// REGRAS DA PARTIDA (sem entrada/saída): turnos, ações, perecíveis, paciência, sorteio

// Utilidades sobre ingredientes (Tabela 1 do enunciado)
const char* nomeIngrediente(char simbolo);     // nullptr se inválido
bool ingredienteValido(char simbolo);
bool requerPreparo(char simbolo);
bool ehPerecivel(char simbolo);
int validadeDe(char simbolo);                  // turnos de validade de um perecível
int quantidadeEstoque(const Partida& p, char simbolo);   // -1 = infinito

// Começa uma partida: enfileira NUM_CLIENTES e sorteia o pedido do primeiro (cache -> AVL)
void iniciarPartida(Jogo& j);

// Cada ação válida consome 1 turno. Retornam false (SEM consumir turno) se a ação é
// inválida; o motivo fica em partida.msg
bool acaoPreparar(Jogo& j, char simbolo);
bool acaoAdicionar(Jogo& j, char simbolo);
bool acaoRemoverTopo(Jogo& j);
void acaoSair(Jogo& j);

#endif
