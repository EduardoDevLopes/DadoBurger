#include "jogo.h"
#include "carga.h"
#include "constants.h"
#include "metricas.h"

using namespace std;

// INICIALIZAÇÃO
bool iniciarJogo(Jogo& j, const string& arquivoPedidos, const string& arquivoHistorico) {
    inicializarHash(j.cache, TAMANHO_HASH, CAPACIDADE_CACHE);
    inicializarLista(j.historico);
    j.arqHistorico = arquivoHistorico;
    if (!carregarPedidos(arquivoPedidos, j.indice, j.estatAVL)) return false;
    j.entradasCarregadas = carregarHistorico(arquivoHistorico.c_str(), j.historico);
    abrirLog(j);   // medicoes.log: métricas da carga (falha no log não impede o jogo)
    return true;
}

// NOVA PARTIDA
void reiniciarPartida(Jogo& j) {
    destruirFila(j.partida.balcao);
    destruirPilha(j.partida.chapa);
    destruirEstoque(j.partida.estoque);
    j.partida = Partida();
    j.estatAVL.buscas = 0;            // métricas de busca valem "durante a partida"
    j.estatAVL.totalComp = 0;
    j.estatAVL.tempoBuscas = 0.0;
}

// ENCERRAMENTO
void encerrarJogo(Jogo& j) {
    reiniciarPartida(j);
    destruirHash(j.cache);   // antes da AVL: o cache aponta para receitas dela
    destruirAVL(j.indice);
    destruirLista(j.historico);
    fecharLog(j);
}
