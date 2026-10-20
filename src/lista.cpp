#include "lista.h"

using namespace std;

// INSERÇÃO
void inserirIngredienteFim(NoIng*& ini, const string& nome) {
    NoIng* novo = new NoIng{nome, nullptr};
    if (ini == nullptr) {
        ini = novo;
        return;
    }
    NoIng* aux = ini;
    while (aux->prox != nullptr) aux = aux->prox;
    aux->prox = novo;
}

// DESTRUIÇÃO
void destruirLista(NoIng*& ini) {
    while (ini != nullptr) {
        NoIng* prox = ini->prox;
        delete ini;
        ini = prox;
    }
}
