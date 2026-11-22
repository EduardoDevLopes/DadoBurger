#ifndef METRICAS_H
#define METRICAS_H
#include <cstdio>
#include "jogo.h"

// RELATÓRIO DE DESEMPENHO E LOG (medicoes.log)
// As funções imprimir* escrevem em 'f' (tela ou log)
void imprimirCarga(FILE* f, const Jogo& j);
void imprimirOrdenacao(FILE* f, const Jogo& j);
void imprimirRelatorio(FILE* f, const Jogo& j);   // relatório completo (fim de partida)

// Abre/recria medicoes.log e grava as métricas da carga
bool abrirLog(Jogo& j);
void registrarRelatorioNoLog(Jogo& j, const char* motivo, int atendidos);
void registrarOrdenacaoNoLog(Jogo& j);
void fecharLog(Jogo& j);

#endif
