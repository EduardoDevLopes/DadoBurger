#ifndef MENU_H
#define MENU_H
#include "constants.h"
#include "jogo.h"

// INTERFACE EM CONSOLE (requisitos mínimos)
// Cada tela segue o padrão desenhar*/atualizar*: quando a parte gráfica for implementada,
// basta reescrever estas funções, sem mexer nas estruturas.

// Mostra o menu inicial (Novo jogo, Como jogar, Histórico, Sair)
void desenharMenu();

// Lê a opção do usuário e atualiza o estado atual
void atualizarMenu(EstadoJogo& estadoAtual);

// Tela estática com as regras (objetivo, ingredientes, ações, vitória e derrota)
void desenharComoJogar();

// Pergunta o critério (alfabético ou pontuação decrescente), ordena uma CÓPIA do histórico,
// mostra o topo da lista e o tempo de ordenação, e acrescenta a medição ao log
void desenharHistorico(Jogo& j);

// Partida completa: nome, turnos, relatório de desempenho e gravação no histórico
void executarPartida(Jogo& j);

#endif
