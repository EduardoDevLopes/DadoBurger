#include <iostream>
#include <string>
#include "constants.h"
#include "jogo.h"
#include "menu.h"

using namespace std;

// FUNÇÃO PRINCIPAL DO JOGO
int main(int argc, char** argv) {
    // INICIALIZAÇÃO
    // Arquivo de pedidos: argv[1] (ex.: versão final) ou o padrão de constants.h
    string arquivoPedidos = (argc > 1) ? argv[1] : ARQUIVO_PEDIDOS;

    Jogo jogo;
    if (!iniciarJogo(jogo, arquivoPedidos)) {
        cerr << "Erro: nao foi possivel abrir " << arquivoPedidos << "\n";
        encerrarJogo(jogo);
        return 1;
    }
    cout << "Pedidos carregados: " << jogo.estatAVL.nos
         << " (altura " << jogo.estatAVL.altura
         << ", rotacoes " << jogo.estatAVL.rotacoes << ")\n";

    EstadoJogo estadoAtual = ESTADO_MENU;

    // LOOP PRINCIPAL (máquina de estados)
    while (estadoAtual != ESTADO_SAIR) {
        switch (estadoAtual) {
            case ESTADO_MENU:
                desenharMenu();
                atualizarMenu(estadoAtual);
                if (estadoAtual == ESTADO_JOGANDO) reiniciarPartida(jogo);   // reset de uma partida
                break;

            case ESTADO_JOGANDO:
                // TODO: Game Loop (turnos, chegada de clientes, paciência, montagem,
                // validade dos lotes, pontuação) e, ao fim, salvar Partida em jogo.historico
                cout << "[Partida em construcao]\n";
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
