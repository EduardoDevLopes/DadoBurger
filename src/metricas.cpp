#include "metricas.h"
#include "constants.h"

void imprimirCarga(FILE* f, const Jogo& j) {
    fprintf(f, "-- AVL: carregamento --\n");
    fprintf(f, "Nos inseridos:           %d\n", j.estatAVL.nos);
    fprintf(f, "Altura resultante:       %d\n", j.estatAVL.altura);
    fprintf(f, "Rotacoes (insercao):     %d\n", j.estatAVL.rotacoes);
    fprintf(f, "Tempo de carregamento:   %.6f s\n", j.estatAVL.tempoCarga);
    fprintf(f, "-- Historico: carregamento --\n");
    fprintf(f, "Entradas carregadas:     %d\n", j.entradasCarregadas);
}

void imprimirOrdenacao(FILE* f, const Jogo& j) {
    fprintf(f, "-- Ordenacao do historico (ao acessar Historico) --\n");
    if (j.estatOrd.acessos == 0) { fprintf(f, "(nenhum acesso ao Historico ate agora)\n"); return; }
    fprintf(f, "Acessos ao Historico: %d\n", j.estatOrd.acessos);
    fprintf(f, "Tamanho: %d entradas (%s)\n", j.estatOrd.tamanho, j.estatOrd.criterio);
    fprintf(f, "Merge Sort: %.6f s\n", j.estatOrd.tempo);
}

void imprimirRelatorio(FILE* f, const Jogo& j) {
    fprintf(f, "=== RELATORIO DE DESEMPENHO ===\n");
    imprimirCarga(f, j);
    fprintf(f, "-- AVL: buscas durante a partida --\n");
    fprintf(f, "Total de buscas:                 %ld\n", j.estatAVL.buscas);
    fprintf(f, "Total de comparacoes:            %ld\n", j.estatAVL.totalComp);
    fprintf(f, "Media de comparacoes por busca:  %.2f\n", j.estatAVL.buscas > 0 ? j.estatAVL.mediaComp() : 0.0);
    fprintf(f, "Tempo total acumulado:           %.6f s\n", j.estatAVL.tempoBuscas);
    long tot = j.cache.hits + j.cache.misses;
    fprintf(f, "-- Tabela hash (sessao) --\n");
    fprintf(f, "Tamanho (m):                     %d\n", j.cache.m);
    fprintf(f, "Entradas ocupadas (n):           %d\n", j.cache.n);
    fprintf(f, "Fator de carga (lambda):         %.4f\n", j.cache.lambda());
    fprintf(f, "Total de hits:                   %ld\n", j.cache.hits);
    fprintf(f, "Total de misses:                 %ld\n", j.cache.misses);
    fprintf(f, "Taxa de acerto:                  %.1f%%\n", tot > 0 ? 100.0 * j.cache.hits / tot : 0.0);
    fprintf(f, "Total de colisoes:               %ld\n", j.cache.colisoes);
    imprimirOrdenacao(f, j);
    fprintf(f, "================================\n");
}

bool abrirLog(Jogo& j) {
    j.log = fopen(ARQUIVO_LOG, "w");   /* criado/sobrescrito a cada execucao */
    if (!j.log) return false;
    fprintf(j.log, "=== MEDICOES - DADO BURGER ===\n");
    imprimirCarga(j.log, j);
    fprintf(j.log, "\n");
    fflush(j.log);
    return true;
}

void registrarRelatorioNoLog(Jogo& j, const char* motivo, int atendidos) {
    if (!j.log) return;
    fprintf(j.log, "\n##### Partida %d encerrada (%s) - clientes atendidos: %d #####\n", j.numPartida, motivo, atendidos);
    imprimirRelatorio(j.log, j);
    fflush(j.log);
}

void registrarOrdenacaoNoLog(Jogo& j) {
    if (!j.log) return;
    fprintf(j.log, "\n##### Acesso %d ao Historico #####\n", j.estatOrd.acessos);
    imprimirOrdenacao(j.log, j);
    fflush(j.log);
}

void fecharLog(Jogo& j) { if (j.log) { fclose(j.log); j.log = nullptr; } }
