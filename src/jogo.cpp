#include "jogo.h"
#include "carga.h"
#include "constants.h"

using namespace std;

// INICIALIZAÇÃO
bool iniciarJogo(Jogo& j, const string& arquivoPedidos) {
    inicializarHash(j.cache, TAMANHO_HASH, CAPACIDADE_CACHE);
    return carregarPedidos(arquivoPedidos, j.indice, j.estatAVL);
}

// NOVA PARTIDA
void reiniciarPartida(Jogo& j) {
    destruirFila(j.balcao);
    destruirPilha(j.chapa);
    j.estoque = Estoque();
    j.turno = 0;
    j.pontuacao = 0;
}

// ENCERRAMENTO
void encerrarJogo(Jogo& j) {
    destruirHash(j.cache);   // antes da AVL: o cache aponta para receitas dela
    destruirAVL(j.indice);
    destruirFila(j.balcao);
    destruirPilha(j.chapa);
}
