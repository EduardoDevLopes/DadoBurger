#include "fila.h"

using namespace std;

// ENFILEIRAR / DESENFILEIRAR
void enfileirarCliente(Fila& f, const Cliente& c) {
    NoFila* novo = new NoFila{c, nullptr};
    if (f.fim == nullptr) f.ini = novo;
    else f.fim->prox = novo;
    f.fim = novo;
    f.tam++;
}

bool desenfileirarCliente(Fila& f, Cliente& out) {
    if (f.ini == nullptr) return false;
    NoFila* aux = f.ini;
    out = aux->c;
    f.ini = aux->prox;
    if (f.ini == nullptr) f.fim = nullptr;   // evita ponteiro pendente (dangling)
    delete aux;
    f.tam--;
    return true;
}

// PACIÊNCIA
int atualizarPaciencia(Fila& f, vector<Cliente>* desistentes) {
    int removidos = 0;
    NoFila* ant = nullptr;
    NoFila* cur = f.ini;
    while (cur != nullptr) {
        cur->c.paciencia--;
        NoFila* prox = cur->prox;
        if (cur->c.paciencia <= 0) {
            if (desistentes != nullptr) desistentes->push_back(cur->c);
            if (ant == nullptr) f.ini = prox;
            else ant->prox = prox;
            if (cur == f.fim) f.fim = ant;
            delete cur;
            f.tam--;
            removidos++;
        } else {
            ant = cur;
        }
        cur = prox;
    }
    return removidos;
}

void destruirFila(Fila& f) {
    Cliente lixo;
    while (desenfileirarCliente(f, lixo)) {}
}
