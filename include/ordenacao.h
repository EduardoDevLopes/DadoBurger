#ifndef ORDENACAO_H
#define ORDENACAO_H
#include "historico.h"

// ORDENAÇÃO DO HISTÓRICO O(n log n)
// Critério: devolve true se 'a' deve vir ANTES de 'b' na ordem final (mesmo padrão do
// esqueleto). Os dois critérios do enunciado:
typedef bool (*CriterioEntrada)(const Entrada& a, const Entrada& b);

bool maiorPontuacao(const Entrada& a, const Entrada& b);   // pontuação decrescente (desempate: nome)
bool ordemAlfabetica(const Entrada& a, const Entrada& b);  // nome, sem distinguir maiúsculas

// Merge Sort (algoritmo escolhido): O(n log n) sempre, estável, O(n) de memória auxiliar
void ordenarHistorico(Entrada* v, int n, CriterioEntrada antes = maiorPontuacao);

// Heap Sort (do esqueleto, adaptado; só para comparação): O(n log n), in-place, não estável
void heapSortHistorico(Entrada* v, int n, CriterioEntrada antes = maiorPontuacao);

// Ordena uma CÓPIA do histórico e devolve o tempo (s) só do algoritmo (a cópia fica fora do
// cronômetro). Se 'saida' != nullptr recebe a cópia ordenada (chamador faz delete[])
double medirOrdenacao(const ListaContigua& hist, CriterioEntrada antes = maiorPontuacao, Entrada** saida = nullptr);

#endif
