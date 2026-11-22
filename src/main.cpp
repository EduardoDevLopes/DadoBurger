#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include "constants.h"
#include "jogo.h"
#include "menu.h"

using namespace std;

// FUNÇÃO PRINCIPAL DO JOGO
// Uso: ./dado_burger <pedidos> <historico> [semente]
int main(int argc, char** argv) {
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <pedidos> <historico> [semente]\n";
        return 1;
    }

    // INICIALIZAÇÃO (antes do menu): pedidos -> AVL; histórico -> lista contígua
    Jogo jogo;
    if (argc > 3) jogo.gerador.seed((unsigned)strtoul(argv[3], nullptr, 10));   // partidas repetíveis
    else { random_device seed; jogo.gerador.seed(seed()); }

    if (!iniciarJogo(jogo, argv[1], argv[2])) {
        cerr << "Erro: nao foi possivel carregar pedidos de '" << argv[1] << "'\n";
        encerrarJogo(jogo);
        return 1;
    }
    cout << "Pedidos carregados: " << jogo.estatAVL.nos
         << " (altura " << jogo.estatAVL.altura
         << ", rotacoes " << jogo.estatAVL.rotacoes
         << ", " << jogo.estatAVL.tempoCarga << " s) | Historico: "
         << jogo.entradasCarregadas << " entradas\n";

    EstadoJogo estadoAtual = ESTADO_MENU;

    // LOOP PRINCIPAL (máquina de estados)
    while (estadoAtual != ESTADO_SAIR) {
        switch (estadoAtual) {
            case ESTADO_MENU:
                desenharMenu();
                atualizarMenu(estadoAtual);
                break;

            case ESTADO_JOGANDO:
                executarPartida(jogo);   // partida completa + relatório + histórico
                estadoAtual = ESTADO_MENU;
                break;

            case ESTADO_COMO_JOGAR:
                desenharComoJogar();
                estadoAtual = ESTADO_MENU;
                break;

            case ESTADO_HISTORICO:
                desenharHistorico(jogo);
                estadoAtual = ESTADO_MENU;
                break;

            default:
                estadoAtual = ESTADO_SAIR;
                break;
        }
    }

    // ENCERRAMENTO
    encerrarJogo(jogo);
    return 0;
}
