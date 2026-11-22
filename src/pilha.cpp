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

char topoIngrediente(const Pilha& p) { return p.topo ? p.topo->ing : '\0'; }

int copiarPilha(const Pilha& p, char* buf, int cap) {
    int n = 0;
    for (const NoPilha* a = p.topo; a != nullptr && n < cap; a = a->prox) buf[n++] = a->ing;
    for (int i = 0, j = n - 1; i < j; i++, j--) { char t = buf[i]; buf[i] = buf[j]; buf[j] = t; }
    return n;
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
