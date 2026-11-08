#include "pilha.h"
#include <algorithm>
#include <vector>

using namespace std;

// OPERAÇÕES BÁSICAS
void pushIngrediente(Pilha& p, const char& ing) {
    p.topo = new NoPilha{ing, p.topo};
    p.tam++;
}

bool popIngrediente(Pilha& p, char* removido) {
    if (p.topo == nullptr) return false;
    NoPilha* aux = p.topo;
    if (removido != nullptr) *removido = aux->ing;
    p.topo = aux->prox;
    delete aux;
    p.tam--;
    return true;
}

void destruirPilha(Pilha& p) {
    while (popIngrediente(p)) {}
}

// VERIFICAÇÃO PILHA x LISTA
bool verificarPedido(const Pilha& p, const NoIng* receita) {
    // Percorre topo -> base e inverte, para ficar na mesma ordem da receita
    vector<char> baseParaTopo;
    for (const NoPilha* a = p.topo; a != nullptr; a = a->prox) baseParaTopo.push_back(a->ing);
    reverse(baseParaTopo.begin(), baseParaTopo.end());

    size_t i = 0;
    for (const NoIng* r = receita; r != nullptr; r = r->prox, i++) {
        if (i >= baseParaTopo.size() || baseParaTopo[i] != r->simbolo) return false;
    }
    return i == baseParaTopo.size();   // não pode sobrar ingrediente na pilha
}
