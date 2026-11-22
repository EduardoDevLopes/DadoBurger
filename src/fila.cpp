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

// PACIÊNCIA (só o cliente da frente)
Cliente* frenteFila(Fila& f) { return f.ini ? &f.ini->c : nullptr; }

int reduzirPacienciaFrente(Fila& f) {
    if (f.ini == nullptr) return -1;
    return --f.ini->c.paciencia;
}

void destruirFila(Fila& f) {
    Cliente lixo;
    while (desenfileirarCliente(f, lixo)) {}
}
