#include "menu.h"
#include <iostream>
#include <limits>

using namespace std;

// RENDERIZAÇÃO DO MENU
void desenharMenu() {
    cout << "\n=== DADO BURGER ===\n"
         << "1. Novo jogo\n"
         << "2. Historico de partidas\n"
         << "3. Sair\n"
         << "Escolha: ";
}

// ATUALIZAÇÃO DO MENU
void atualizarMenu(EstadoJogo& estadoAtual) {
    int opcao = 0;
    if (!(cin >> opcao)) {
        if (cin.eof()) { estadoAtual = ESTADO_SAIR; return; }   // entrada encerrada
        cin.clear();                                              // texto não numérico
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opcao invalida.\n";
        return;
    }
    switch (opcao) {
        case 1: estadoAtual = ESTADO_JOGANDO;   break;
        case 2: estadoAtual = ESTADO_HISTORICO; break;
        case 3: estadoAtual = ESTADO_SAIR;      break;
        default: cout << "Opcao invalida.\n";   break;
    }
}

// TELA DE HISTÓRICO
void desenharHistorico(const Jogo& j) {
    cout << "\n=== HISTORICO (por pontuacao) ===\n";
    if (j.historico.empty()) {
        cout << "Nenhuma partida registrada.\n";
        return;
    }
    vector<Partida> copia = j.historico;   // ordena cópia: o histórico original não muda
    ordenarHistorico(copia, maiorPontuacao);
    for (size_t i = 0; i < copia.size() && i < (size_t)HISTORICO_EXIBIDO; i++)
        cout << i + 1 << ". partida " << copia[i].id << " - " << copia[i].pontuacao
             << " pts, " << copia[i].tempoAtendimento << " turnos\n";
    cout << "Tempo de ordenacao (" << copia.size() << " partidas): "
         << medirOrdenacao(j.historico) << " s\n";
}
