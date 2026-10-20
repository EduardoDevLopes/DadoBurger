#ifndef HISTORICO_H
#define HISTORICO_H
#include <vector>

// HISTÓRICO DE PARTIDAS E ORDENAÇÃO O(n log n)
struct Partida {
    int id;
    int pontuacao;
    int tempoAtendimento;   // em turnos
};

// Critério: devolve true se 'a' deve vir ANTES de 'b' na ordem final
typedef bool (*CriterioPartida)(const Partida& a, const Partida& b);

bool maiorPontuacao(const Partida& a, const Partida& b);   // pontuação decrescente
bool menorTempo(const Partida& a, const Partida& b);       // tempo crescente

// Ordena o histórico com Heap Sort (O(n log n) no pior caso, in-place, não estável)
void ordenarHistorico(std::vector<Partida>& hist, CriterioPartida antes = maiorPontuacao);

// Ordena uma CÓPIA do histórico e devolve o tempo gasto, em segundos
double medirOrdenacao(const std::vector<Partida>& hist, CriterioPartida antes = maiorPontuacao);

#endif
