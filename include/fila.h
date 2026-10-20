#ifndef FILA_H
#define FILA_H
#include <vector>

// FILA (FIFO) - balcão de atendimento
struct Cliente {
    int id;
    int idPedido;     // chave do pedido na AVL
    int paciencia;    // turnos restantes antes de desistir
};

struct NoFila {
    Cliente c;
    NoFila* prox;
};

struct Fila {
    NoFila* ini = nullptr;
    NoFila* fim = nullptr;
    int tam = 0;
};

// Adiciona cliente no final da fila. Complexidade O(1)
void enfileirarCliente(Fila& f, const Cliente& c);

// Atende e remove o cliente da frente. Retorna false se vazia. O(1)
bool desenfileirarCliente(Fila& f, Cliente& out);

// Decrementa a paciência de todos e remove os que chegaram a 0. O(n)
// Retorna o número de desistentes; se 'desistentes' != nullptr, preenche com eles
int atualizarPaciencia(Fila& f, std::vector<Cliente>* desistentes = nullptr);

// Libera todos os nós da fila
void destruirFila(Fila& f);

#endif
