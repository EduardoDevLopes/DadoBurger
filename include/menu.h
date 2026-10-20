#ifndef MENU_H
#define MENU_H
#include "constants.h"
#include "jogo.h"

// INTERFACE EM CONSOLE (requisitos mínimos)
// Cada tela segue o padrão desenhar*/atualizar*: quando a parte gráfica (raylib)
// for implementada, basta reescrever estas funções, sem mexer nas estruturas.

// Mostra o menu inicial
void desenharMenu();

// Lê a opção do usuário e atualiza o estado atual
void atualizarMenu(EstadoJogo& estadoAtual);

// Mostra o histórico ordenado por pontuação (top N) e o tempo de ordenação
void desenharHistorico(const Jogo& j);

#endif
